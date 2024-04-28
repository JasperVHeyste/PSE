#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "XMLprocessor.h"
#include "PrintingSystem.h"
#include "Output.h"

/**
 * function to test if two given files have the same contents
 * @param leftFileName the first file
 * @param rightFileName the second file to be compared with the first file
 * @return true if both files have the same content, false if not
 */
bool FileCompare(const std::string leftFileName, const std::string rightFileName) { //van tictactoe14
    ifstream leftFile, rightFile;
    char leftRead, rightRead;
    bool result;

    //test if both files can be opened
    leftFile.open(leftFileName.c_str());
    if (!leftFile.is_open()) {
        return false;
    };
    rightFile.open(rightFileName.c_str());
    if (!rightFile.is_open()) {
        leftFile.close();
        return false;
    };

    result = true; // files exist and are open; assume equality unless a counterexamples shows up.
    while (result && leftFile.good() && rightFile.good()) {
        leftFile.get(leftRead);
        rightFile.get(rightRead);
        result = (leftRead == rightRead);
    };
    if (result) {
        // last read was still equal; are we at the end of both files ?
        result = (!leftFile.good()) && (!rightFile.good());
    };

    leftFile.close();
    rightFile.close();
    return result;
}

/**
 * Converts the vector from an xml that was already read in into a text file
 * @param input the vector from the read-in xml
 * @param outputfilename the filename of the textfile created from this vector
 */
void processedxmlToTextFile(vector<map<string,string>> input, const char* outputfilename){
    std::ofstream outputfile;
    outputfile.open(outputfilename);

    for (unsigned int i = 0; i < input.size(); i++){
        string objecttype = input[i]["objecttype"];

        if (objecttype == "device"){
            outputfile << objecttype << endl << input[i]["name"] << endl << input[i]["emissions"] << endl << input[i]["speed"] << endl << input[i]["type"] << endl << input[i]["cost"] << endl << endl;
        }
        if (objecttype == "job"){
            outputfile << objecttype << endl << input[i]["jobNumber"] << endl << input[i]["pageCount"] << endl << input[i]["userName"] << endl << input[i]["type"] << endl;
            if (input[i].count("compNumber")){
                outputfile << input[i]["compNumber"] << endl;
            }
            outputfile << endl;
        }
        if (objecttype == "compensation"){
            outputfile << objecttype << endl << input[i]["name"] << endl << input[i]["compNumber"] << endl;
            outputfile << endl;
        }
    }
}

/**
 * Tests for reading input
 */
class InputTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from subclasses.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    XMLprocessor xmlp;
};

TEST_F(InputTest, correctemptyxml) {
    std::vector<std::map<std::string, std::string>> input;
    input = xmlp.readXML("testempty.xml");
    int objectamount = input.size();
    EXPECT_EQ(0, objectamount);
}

TEST_F(InputTest, correctxmls) {
    std::vector<std::map<std::string, std::string>> input;
    const char* outputfilename;

    input = xmlp.readXML("testvalid1.xml");
    outputfilename = "testvalid1.txt";
    processedxmlToTextFile(input, outputfilename);
    EXPECT_TRUE(FileCompare("testvalid1.txt", "testvalid1_expected.txt"));

    input = xmlp.readXML("testvalid2.xml");
    outputfilename = "testvalid2.txt";
    processedxmlToTextFile(input, outputfilename);
    EXPECT_TRUE(FileCompare("testvalid2.txt", "testvalid2_expected.txt"));
}

TEST_F(InputTest, wrongxml) {
    std::vector<std::map<std::string, std::string>> input;
    ofstream errorfile;
    errorfile.open("testwrongxml.txt");

    input = xmlp.readXML("thisfileshouldnotexist.xml", errorfile);
    int objectamount = input.size();
    EXPECT_EQ(0, objectamount);

    input = xmlp.readXML("testfaultyxml1.xml", errorfile);
    objectamount = input.size();
    EXPECT_EQ(0, objectamount);

    input = xmlp.readXML("testfaultyxml2.xml", errorfile);
    objectamount = input.size();
    EXPECT_EQ(0, objectamount);

    EXPECT_TRUE(FileCompare("testwrongxml.txt", "testwrongxml_expected.txt"));
}

TEST_F(InputTest, testinvalidinfoxml) {
    std::ofstream errorfile;
    errorfile.open("testinvalidinfoxml.txt");

    xmlp.readXML("testinvalidinfo1.xml", errorfile);
    //DEVICE: non-int emission and speed
    //JOB: non-int jobnumber and pagecount
    //JOB: negative pagecount, unrecognized type
    //DEVICE: non-int cost, unrecognized type
    //COMPENSATION: non-int compnumber
    xmlp.readXML("testinvalidinfo2.xml", errorfile);
    //DEVICE: missing emissions element
    //JOB: missing jobnumber and username
    xmlp.readXML("testinvalidinfo3.xml", errorfile); //unrecognizable parameter for job and device

    EXPECT_TRUE(FileCompare("testinvalidinfoxml.txt", "testinvalidinfoxml_expected.txt"));
}

TEST_F(InputTest, testinconsistentprintingsystem) {
    std::ofstream errorfile;
    errorfile.open("testinconsistentprintsys.txt");

    std::vector<std::map<std::string, std::string>> input;
    input = xmlp.readXML("testrepeatjobnr.xml", errorfile); //two jobs with same jobNumber
    int objectamount = input.size();
    EXPECT_EQ(0, objectamount);
    input = xmlp.readXML("testrepeatcompnr.xml", errorfile); //two compensations with same compNumber
    objectamount = input.size();
    EXPECT_EQ(0, objectamount);
    EXPECT_TRUE(FileCompare("testinconsistentprintsys.txt", "testinconsistentprintsys_expected.txt"));
}

TEST_F(InputTest, testunrecognizableelementxml) {
    std::ofstream errorfile;
    errorfile.open("testunrecognizableelementxml.txt");

    std::vector<std::map<std::string, std::string>> input;
    xmlp.readXML("testunrecognizableelement1.xml", errorfile);
    xmlp.readXML("testunrecognizableelement2.xml", errorfile);
    EXPECT_TRUE(FileCompare("testunrecognizableelementxml.txt", "testunrecognizableelementxml_expected.txt"));
}

TEST_F(InputTest, checkstringisposint) {
    EXPECT_TRUE(xmlp.checkStringIsPositiveInt("12"));
    EXPECT_TRUE(xmlp.checkStringIsPositiveInt("9"));
    EXPECT_TRUE(xmlp.checkStringIsPositiveInt("3987524"));
    EXPECT_FALSE(xmlp.checkStringIsPositiveInt("a"));
    EXPECT_FALSE(xmlp.checkStringIsPositiveInt("-1"));
    EXPECT_FALSE(xmlp.checkStringIsPositiveInt("hello world"));
}

TEST_F(InputTest, contracttests) {
    EXPECT_TRUE(xmlp.properlyInitialized());
    EXPECT_DEATH(xmlp.readXML("testwrongxml.txt"), "Assertion.*failed");
    EXPECT_DEATH(xmlp.readXML("testnonxml"), "Assertion.*failed");
}

/**
 * Tests for correct processing of data
 */
class PrintSysTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from subclasses.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    PrintingSystem ps;
    XMLprocessor xmlp;
};

TEST_F(PrintSysTest, contracttests) {
    EXPECT_TRUE(ps.properlyInitialized());
    EXPECT_DEATH(xmlp.implementXML("testnonxml.txt", ps), "Assertion.*failed");
}

TEST_F(PrintSysTest, OutputTest1) {
    std::ofstream outputfile;
    outputfile.open("testoutput1.txt");
    xmlp.implementXML("testoutput1.xml", ps);
    ps.automatedJob(outputfile);
    EXPECT_TRUE(FileCompare("testoutput1.txt", "testoutput1_expected.txt"));
    EXPECT_EQ(ps.getEmissions(), 33);
}

TEST_F(PrintSysTest, OutputTest2) {
    std::ofstream outputfile;
    outputfile.open("testoutput2.txt");
    xmlp.implementXML("testoutput2.xml", ps);
    ps.automatedJob(outputfile);
    EXPECT_TRUE(FileCompare("testoutput2.txt", "testoutput2_expected.txt"));
    EXPECT_EQ(ps.getEmissions(), 24);
}

TEST_F(PrintSysTest, OutputTest3) {
    std::ofstream outputfile;
    outputfile.open("testoutput3.txt");
    xmlp.implementXML("testoutput3.xml", ps);
    ps.automatedJob(outputfile);
    EXPECT_TRUE(FileCompare("testoutput3.txt", "testoutput3_expected.txt"));
    EXPECT_EQ(ps.getEmissions(), 6778);
}

TEST_F(PrintSysTest, OnePrinterMultipleJobs) {
    std::ofstream outputfile;
    outputfile.open("testoneprintermultiplejobs.txt");
    xmlp.implementXML("testoneprintermultiplejobs.xml", ps);
    ps.automatedJob(outputfile);
    EXPECT_TRUE(FileCompare("testoneprintermultiplejobs.txt", "testoneprintermultiplejobs_expected.txt"));
}

TEST_F(PrintSysTest, MultiplePrintersOneJob) {
    std::ofstream outputfile;
    outputfile.open("testmultipleprintersonejob.txt");
    xmlp.implementXML("testmultipleprintersonejob.xml", ps);
    ps.automatedJob(outputfile);
    EXPECT_TRUE(FileCompare("testmultipleprintersonejob.txt", "testmultipleprintersonejob_expected.txt"));
}

TEST_F(PrintSysTest, NoPrinterAvailableForType) {
    std::ofstream outputfile;
    outputfile.open("NoPrinterAvailableForType.txt");
    xmlp.implementXML("NoPrinterAvailableForType.xml", ps);
    ps.automatedJob(outputfile);
    EXPECT_TRUE(FileCompare("NoPrinterAvailableForType.txt", "NoPrinterAvailableForType_expected.txt"));
}

TEST_F(PrintSysTest, NoJobs) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    xmlp.implementXML("testnojobs.xml", ps);
    ps.assignAllJobs();
    ps.proccesJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "All jobs ready\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

TEST_F(PrintSysTest, NoPrinters) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    xmlp.implementXML("testnoprinters.xml", ps);
    ps.assignAllJobs();
    ps.proccesJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "No printers to assign job\nNo printers available for job type: bw\nNo printers available for job type: color\nNo printers available for job type: scan\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

/**
 * tests for correct output
 */
class OutputTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from subclasses.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    PrintingSystem ps;
    XMLprocessor xmlp;
    Output o;
};

TEST_F(OutputTest, noprinters){
    TiXmlDocument doc;
    xmlp.implementXML("testnoprinters.xml", ps);
    o.simpleOutput(&ps);
    o.advancedOutput(&ps);
    EXPECT_TRUE(FileCompare("status_report0.txt", "simple_output_noprinterstest.txt"));
    EXPECT_TRUE(FileCompare("advanced_status_report0.txt", "advanced_output_noprinterstest.txt"));
}

// test with no jobs
TEST_F(OutputTest, nojobs){
    TiXmlDocument doc;
    xmlp.implementXML("testnojobs.xml", ps);
    o.simpleOutput(&ps);
    o.advancedOutput(&ps);
    EXPECT_TRUE(FileCompare("status_report0.txt", "simple_output_nojobstest.txt"));
    EXPECT_TRUE(FileCompare("advanced_status_report0.txt", "advanced_output_nojobstest.txt"));
}

// test with normal case, 2 printers, 3 jobs
TEST_F(OutputTest, normalcase){
    TiXmlDocument doc;
    xmlp.implementXML("testnormalcase1.xml", ps);

    ps.assignAllJobs();
    o.simpleOutput(&ps);
    o.advancedOutput(&ps);
    ps.proccesJob();
    o.simpleOutput(&ps);
    o.advancedOutput(&ps);
    ps.proccesJob();
    o.simpleOutput(&ps);
    o.advancedOutput(&ps);
    ps.proccesJob();

    EXPECT_TRUE(FileCompare("status_report0.txt", "simple_output_normalcase1.1.txt"));
    EXPECT_TRUE(FileCompare("status_report1.txt", "simple_output_normalcase1.2.txt"));
    EXPECT_TRUE(FileCompare("status_report2.txt", "simple_output_normalcase1.3.txt"));

    EXPECT_TRUE(FileCompare("advanced_status_report0.txt", "advanced_output_normalcase1.1.txt"));
    EXPECT_TRUE(FileCompare("advanced_status_report1.txt", "advanced_output_normalcase1.2.txt"));
    EXPECT_TRUE(FileCompare("advanced_status_report2.txt", "advanced_output_normalcase1.3.txt"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
