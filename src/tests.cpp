#include "gtest/gtest.h"
#include <iostream>

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

#include "readXML.h"

TEST_F(InputTest, emptyxml) {
    /*const char* filename = "testinput1.xml";

    std::vector<std::map<std::string, std::string>> output;
    output = readXML(filename);


    EXPECT_EQ(5, max);*/
}

