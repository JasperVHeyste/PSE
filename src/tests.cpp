#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "readXML.h"

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
};

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
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
    input = readXML("testempty.xml");
    int objectamount = input.size();
    EXPECT_EQ(0, objectamount);
}

TEST_F(InputTest, correctxmls) {
    std::vector<std::map<std::string, std::string>> input;
    const char* outputfilename;

    input = readXML("testvalid1.xml");
    outputfilename = "testvalid1.txt";
    processedxmlToTextFile(input, outputfilename);
    EXPECT_TRUE(FileCompare("testvalid1.txt", "testvalid1_expected.txt"));

    input = readXML("testvalid2.xml");
    outputfilename = "testvalid2.txt";
    processedxmlToTextFile(input, outputfilename);
    EXPECT_TRUE(FileCompare("testvalid2.txt", "testvalid2_expected.txt"));
}

TEST_F(InputTest, nonexistentxml) {
    std::vector<std::map<std::string, std::string>> input;
    ofstream errorfile;
    errorfile.open("testnonexistentxml.txt");

    input = readXML("thisfileshouldnotexist.xml", errorfile);
    int objectamount = input.size();
    EXPECT_EQ(0, objectamount);
    EXPECT_TRUE(FileCompare("testnonexistentxml.txt", "testnonexistentxml_expected.txt"));
}

TEST_F(InputTest, checkstringforposint) {
    EXPECT_TRUE(stringIsPositiveInteger("12"));
    EXPECT_TRUE(stringIsPositiveInteger("9"));
    EXPECT_TRUE(stringIsPositiveInteger("3987524"));
    EXPECT_FALSE(stringIsPositiveInteger("a"));
    EXPECT_FALSE(stringIsPositiveInteger("-1"));
    EXPECT_FALSE(stringIsPositiveInteger("hello world"));
}


TEST_F(InputTest, testinvalidinfoxml) {
    std::ofstream outputfile;
    outputfile.open("testinvalidinfoxml.txt");

    std::vector<std::map<std::string, std::string>> input;
    readXML("testinvalidinfo1.xml", outputfile); //non-int emission
    readXML("testinvalidinfo2.xml", outputfile); //non-int speed
    readXML("testinvalidinfo3.xml", outputfile); //non-int jobnumber
    readXML("testinvalidinfo4.xml", outputfile); //non-int pagecount
    readXML("testinvalidinfo5.xml", outputfile); //missing element for device
    readXML("testinvalidinfo6.xml", outputfile); //missing element for job
    readXML("testinvalidinfo7.xml", outputfile); //negative int
    EXPECT_TRUE(FileCompare("testinvalidinfoxml.txt", "testinvalidinfoxml_expected.txt"));
}

TEST_F(InputTest, testunrecognizableelementxml) {
    std::ofstream outputfile;
    outputfile.open("testunrecognizableelementxml.txt");

    std::vector<std::map<std::string, std::string>> input;
    readXML("testunrecognizableelement1.xml", outputfile);
    readXML("testunrecognizableelement2.xml", outputfile);
    EXPECT_TRUE(FileCompare("testunrecognizableelementxml.txt", "testunrecognizableelementxml_expected.txt"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
