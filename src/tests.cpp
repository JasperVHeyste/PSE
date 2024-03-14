#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "XMLprocessor.h"

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

void processedxmlToTextFile(vector<map<string,string>> input, const char* outputfilename){
    std::ofstream outputfile;
    outputfile.open(outputfilename);

    for (unsigned int i = 0; i < input.size(); i++){
        string type = input[i]["type"];

        if (type == "device"){
            outputfile << type << endl << input[i]["name"] << endl << input[i]["emissions"] << endl << input[i]["speed"] << endl << endl;
        }
        if (type == "job"){
            outputfile << type << endl << input[i]["jobNumber"] << endl << input[i]["pageCount"] << endl << input[i]["userName"] << endl << endl;
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

    xmlp.readXML("testinvalidinfo1.xml", errorfile); //non-int emission
    xmlp.readXML("testinvalidinfo2.xml", errorfile); //non-int speed
    xmlp.readXML("testinvalidinfo3.xml", errorfile); //non-int jobnumber
    xmlp.readXML("testinvalidinfo4.xml", errorfile); //non-int pagecount
    xmlp.readXML("testinvalidinfo5.xml", errorfile); //missing element for device
    xmlp.readXML("testinvalidinfo6.xml", errorfile); //missing element for job
    xmlp.readXML("testinvalidinfo7.xml", errorfile); //negative int

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
    EXPECT_DEATH(xmlp.readXML("testnonxml.txt"), "Assertion.*failed");
    EXPECT_DEATH(xmlp.readXML("testnonxml"), "Assertion.*failed");
}

#include "PrintingSystem.h"

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
