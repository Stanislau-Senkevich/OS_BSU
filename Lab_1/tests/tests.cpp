#include <gtest/gtest.h>
#include <sstream>
#include "../src/creator.cpp"

TEST(GetRecordTest, ValidInput) {
    employee record;
    std::istringstream input("1234\nJohn Doe\n40.5\n");
    std::ostringstream output;

    getRecord(&record, 0, input, output);

    EXPECT_EQ(record.ID, 1234);
    EXPECT_EQ(record.name, "John Doe");
    EXPECT_DOUBLE_EQ(record.hours, 40.5);

    std::string expected_output = "Employee 1:\nEnter ID: \nEnter name: \nEnter hours: \n";
    EXPECT_EQ(output.str(), expected_output);
}

TEST(GetRecordTest, InvalidIDInput) {
    employee record;
    std::istringstream input("abcd\n1234\nJohn Doe\n40.5\n");
    std::ostringstream output;

    getRecord(&record, 0, input, output);

    EXPECT_EQ(record.ID, 1234);
    EXPECT_EQ(record.name, "John Doe");
    EXPECT_DOUBLE_EQ(record.hours, 40.5);

    std::string expected_output = "Employee 1:\nEnter ID: \nEnter name: \nEnter hours: \n";
    EXPECT_EQ(output.str(), expected_output);
}

TEST(GetRecordTest, EmptyNameInput) {
    employee record;
    std::istringstream input("1234\n\nJohn Doe\n40.5\n");
    std::ostringstream output;

    getRecord(&record, 0, input, output);

    EXPECT_EQ(record.ID, 1234);
    EXPECT_EQ(record.name, "John Doe");
    EXPECT_DOUBLE_EQ(record.hours, 40.5);

    std::string expected_output = "Employee 1:\nEnter ID: \nEnter name: \nEnter hours: \n";
    EXPECT_EQ(output.str(), expected_output);
}
