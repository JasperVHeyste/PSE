#include "gtest/gtest.h"


class LargestTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

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

TEST_F(LargestTest, Test1) {
std::vector<int> some_numbers = std::vector<int>();
some_numbers.push_back(3);
some_numbers.push_back(5);
some_numbers.push_back(-11);

int max = largest2(&some_numbers);

EXPECT_EQ(5, max);
}

TEST_F(LargestTest, Test2) {
std::vector<int> some_numbers = std::vector<int>();
some_numbers.push_back(-10);
some_numbers.push_back(-9);
some_numbers.push_back(-11);

int max = largest2(&some_numbers);

EXPECT_EQ(-9, max);
}

TEST_F(LargestTest, Test3) {
std::vector<int> some_numbers = std::vector<int>();
some_numbers.push_back(-11);

int max = largest2(&some_numbers);

EXPECT_EQ(-11, max);
}

TEST_F(LargestTest, Test4) {
std::vector<int> some_numbers = std::vector<int>();
some_numbers.push_back(-11);
some_numbers.push_back(-11);
some_numbers.push_back(-11);

int max = largest2(&some_numbers);

EXPECT_EQ(-11, max);
}

TEST_F(LargestTest, Test5) {
std::vector<int> some_numbers = std::vector<int>();
some_numbers.push_back(-11);
some_numbers.push_back(-11);
some_numbers.push_back(-11);
some_numbers.push_back(5);

int max = largest2(&some_numbers);

EXPECT_EQ(5, max);
}
