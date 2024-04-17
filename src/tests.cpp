#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "XMLprocessor.h"
#include "PrintingSystem.h"

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
            outputfile << objecttype << endl << input[i]["name"] << endl << input[i]["emissions"] << endl << input[i]["speed"] << endl;
            if (input[i].count("type")){
                outputfile << input[i]["type"] << endl;
            }
            if (input[i].count("cost")){
                outputfile << input[i]["cost"] << endl;
            }
            outputfile << endl;
        }
        if (objecttype == "job"){
            outputfile << objecttype << endl << input[i]["jobNumber"] << endl << input[i]["pageCount"] << endl << input[i]["userName"] << endl;
            if (input[i].count("type")){
                outputfile << input[i]["type"] << endl;
            }
            if (input[i].count("compensation")){
                outputfile << input[i]["compensation"] << endl;
            }
            outputfile << endl;
        }
    }
}


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
    EXPECT_DEATH(ps.implementXML("testnonxml.txt", xmlp), "Assertion.*failed");
}

TEST_F(PrintSysTest, OutputTest1) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    ps.implementXML("testoutput1.xml", xmlp);
    ps.automatedJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "Printer 'Office_Printer1' finished job:\n    Number: 1\n    Submitted by 'SergeDemeyer'\n    2 pages\nPrinter 'Office_Printer2' finished job:\n    Number: 2\n    Submitted by 'anonymous_user'\n    3 pages\nPrinter 'Office_Printer1' finished job:\n    Number: 3\n    Submitted by 'anonymous_user'\n    3 pages\nPrinter 'Office_Printer2' finished job:\n    Number: 4\n    Submitted by 'anonymous_user'\n    3 pages\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

TEST_F(PrintSysTest, OutputTest2) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    ps.implementXML("testoutput2.xml", xmlp);
    ps.automatedJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "Printer 'Office_Printer1' finished job:\n    Number: 1\n    Submitted by 'SergeDemeyer'\n    2 pages\nPrinter 'Office_Printer2' finished job:\n    Number: 2\n    Submitted by 'anonymous_user'\n    3 pages\nPrinter 'Office_Printer1' finished job:\n    Number: 3\n    Submitted by 'anonymous_user'\n    3 pages\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

TEST_F(PrintSysTest, OutputTest3) {
    std::ofstream outputfile;
    outputfile.open("testoutput3.txt");
    ps.implementXML("testoutput3.xml", xmlp);
    ps.automatedJob(outputfile);
    EXPECT_TRUE(FileCompare("testoutput3.txt", "testoutput3_expected.txt"));
}

TEST_F(PrintSysTest, OnePrinterMultipleJobs) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    ps.implementXML("testoneprintermultiplejobs.xml", xmlp);
    ps.automatedJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "Printer 'Office_Printer1' finished job:\n    Number: 1\n    Submitted by 'SergeDemeyer'\n    2 pages\nPrinter 'Office_Printer1' finished job:\n    Number: 2\n    Submitted by 'anonymous_user'\n    3 pages\nPrinter 'Office_Printer1' finished job:\n    Number: 3\n    Submitted by 'anonymous_user'\n    4 pages\nPrinter 'Office_Printer1' finished job:\n    Number: 4\n    Submitted by 'anonymous_user'\n    5 pages\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

TEST_F(PrintSysTest, MultiplePrintersOneJob) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    ps.implementXML("testmultipleprintersonejob.xml", xmlp);
    ps.automatedJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "Printer 'Office_Printer4' finished job:\n    Number: 1\n    Submitted by 'SergeDemeyer'\n    2 pages\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

TEST_F(PrintSysTest, MultiplePrintersMultipleJobs) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    ps.implementXML("testmultipleprintersmultiplejobs.xml", xmlp);
    ps.automatedJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "Printer 'Office_Printer4' finished job:\n    Number: 1\n    Submitted by 'SergeDemeyer'\n    2 pages\nPrinter 'Office_Printer3' finished job:\n    Number: 2\n    Submitted by 'anonymous_user'\n    3 pages\nPrinter 'Office_Printer2' finished job:\n    Number: 3\n    Submitted by 'anonymous_user'\n    3 pages\nPrinter 'Office_Printer1' finished job:\n    Number: 4\n    Submitted by 'anonymous_user'\n    3 pages\nPrinter 'Office_Printer4' finished job:\n    Number: 5\n    Submitted by 'anonymous_user'\n    3 pages\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

TEST_F(PrintSysTest, NoJobs) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    ps.implementXML("testnojobs.xml", xmlp);
    ps.assignJob();
    ps.proccesJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "All jobs ready\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

TEST_F(PrintSysTest, NoPrinters) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    ps.implementXML("testnoprinters.xml", xmlp);
    ps.assignJob();
    ps.proccesJob();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "No printers to assign job\n";
    EXPECT_TRUE(buffer.str() == expectedOutput);
}

/**
 * tests for correct output
 */
class SimpleOutputTest: public ::testing::Test {
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

TEST_F(SimpleOutputTest, noprinters){
    TiXmlDocument doc;
    ps.implementXML("testnoprinters.xml", xmlp);
    ps.simpleOutput();
    EXPECT_TRUE(FileCompare("status_report0.txt", "testnoprinters_expected.txt"));
}

// test with no jobs
TEST_F(SimpleOutputTest, nojobs){
    TiXmlDocument doc;
    ps.implementXML("testnojobs.xml", xmlp);
    ps.simpleOutput();
    EXPECT_TRUE(FileCompare("status_report0.txt", "testnojobs_expected.txt"));
}

// test with normal case, 2 printers, 3 jobs
TEST_F(SimpleOutputTest, normalcase){
    TiXmlDocument doc;
    ps.implementXML("testnormalcase1.xml", xmlp);

    std::ofstream outputfile;
    outputfile.open("temp.txt");

    while(not ps.isQueueEmpty()){
        ps.simpleOutput();
        ps.assignJob();
        ps.simpleOutput();
        ps.proccesJob(outputfile);
        ps.simpleOutput();
    }

    EXPECT_TRUE(FileCompare("status_report0.txt", "testnormalcase1_expected1.txt"));
    EXPECT_TRUE(FileCompare("status_report1.txt", "testnormalcase1_expected2.txt"));
    EXPECT_TRUE(FileCompare("status_report2.txt", "testnormalcase1_expected3.txt"));
    EXPECT_TRUE(FileCompare("status_report3.txt", "testnormalcase1_expected4.txt"));
    EXPECT_TRUE(FileCompare("status_report4.txt", "testnormalcase1_expected5.txt"));
    EXPECT_TRUE(FileCompare("status_report5.txt", "testnormalcase1_expected6.txt"));
}

// test with normal case, 1 printer, 2 jobs
TEST_F(SimpleOutputTest, normalcase2) {
    ps.implementXML("testnormalcase2.xml", xmlp);

    std::ofstream outputfile;
    outputfile.open("temp.txt");

    while(not ps.isQueueEmpty()){
        ps.simpleOutput();
        ps.assignJob();
        ps.simpleOutput();
        ps.proccesJob(outputfile);
        ps.simpleOutput();
    }

    EXPECT_TRUE(FileCompare("status_report0.txt", "testnormalcase2_expected1.txt"));
    EXPECT_TRUE(FileCompare("status_report1.txt", "testnormalcase2_expected2.txt"));
    EXPECT_TRUE(FileCompare("status_report2.txt", "testnormalcase2_expected3.txt"));
    EXPECT_TRUE(FileCompare("status_report3.txt", "testnormalcase2_expected4.txt"));
    EXPECT_TRUE(FileCompare("status_report4.txt", "testnormalcase2_expected5.txt"));
    EXPECT_TRUE(FileCompare("status_report5.txt", "testnormalcase2_expected6.txt"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
