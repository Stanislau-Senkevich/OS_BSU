#include <gtest/gtest.h>
#include "employee.h"

TEST(WorkerTest, GenerateCountOfClient) {
    int clientCount = generateCountOfClient();
    EXPECT_GE(clientCount, 2);
    EXPECT_LE(clientCount, 6);
}

TEST(WorkerTest, FindEmp) {
    qsort(emps, empCount, employeeSize, empCmp);
    employee* foundEmp = findEmp(2);
    ASSERT_NE(foundEmp, nullptr);
    EXPECT_EQ(foundEmp->num, 2);
    EXPECT_EQ(foundEmp->name, "Bob");
    EXPECT_EQ(foundEmp->hours, 35);

    employee* notFoundEmp = findEmp(4);
    EXPECT_EQ(notFoundEmp, nullptr);
}

TEST(WorkerTest, SortEmps) {
    emps[0] = {3, "Charlie", 45};
    emps[1] = {1, "Alice", 40};
    emps[2] = {2, "Bob", 35};

    sortEmps();
    EXPECT_EQ(emps[0].num, 1);
    EXPECT_EQ(emps[1].num, 2);
    EXPECT_EQ(emps[2].num, 3);
}

TEST(WorkerTest, WriteReadData) {
    std::string fileName = "test_emps.bin";

    writeData(fileName);

    delete[] emps;
    empCount = 3;
    emps = new employee[empCount];

    std::ifstream fin(fileName, std::ios::in | std::ios::binary);
    fin.read(reinterpret_cast<char*>(emps), employeeSize * empCount);
    fin.close();

    EXPECT_EQ(emps[0].num, 1);
    EXPECT_EQ(emps[0].name, "Alice");
    EXPECT_EQ(emps[0].hours, 40);

    EXPECT_EQ(emps[1].num, 2);
    EXPECT_EQ(emps[1].name, "Bob");
    EXPECT_EQ(emps[1].hours, 35);

    EXPECT_EQ(emps[2].num, 3);
    EXPECT_EQ(emps[2].name, "Charlie");
    EXPECT_EQ(emps[2].hours, 45);

    remove(fileName.c_str());
}

TEST(WorkerTest, ReadDataSTD) {
    empCount = 2;
    std::istringstream input("1 John 40 2 Jane 35");
    std::streambuf* cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    readDataSTD();

    EXPECT_EQ(emps[0].num, 1);
    EXPECT_EQ(emps[0].name, "John");
    EXPECT_EQ(emps[0].hours, 40);

    EXPECT_EQ(emps[1].num, 2);
    EXPECT_EQ(emps[1].name, "Jane");
    EXPECT_EQ(emps[1].hours, 35);

    std::cin.rdbuf(cinbuf);
}

class WorkerTest : public ::testing::Test {
protected:
    void SetUp() override {
        InitializeCriticalSection(&empsCS);
    }

    void TearDown() override {
        DeleteCriticalSection(&empsCS);
    }
};