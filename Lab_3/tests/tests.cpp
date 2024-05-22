#include <gtest/gtest.h>
#include <windows.h>
#include "worker.h"

class WorkerTest : public ::testing::Test {
protected:
    void SetUp() override {
        InitializeCriticalSection(&cs);
        fromMain = new HANDLE[2];
        fromThread = new HANDLE[2];
    }

    void TearDown() override {
        DeleteCriticalSection(&cs);
        delete[] fromMain;
        delete[] fromThread;
    }

    CRITICAL_SECTION cs;
    HANDLE* fromMain;
    HANDLE* fromThread;
};

TEST_F(WorkerTest, InitThread) {
    int arr[10] = {0};
    Worker::Config* cfg = Worker::initThread(0, arr, 10, &cs, fromMain, fromThread);
    
    ASSERT_NE(cfg, nullptr);
    EXPECT_EQ(cfg->num, 1);
    EXPECT_EQ(cfg->arrSize, 10);
    EXPECT_EQ(cfg->arr, arr);
    EXPECT_EQ(cfg->cs, &cs);
    EXPECT_EQ(cfg->fromMain, fromMain);
    EXPECT_EQ(cfg->fromThread, fromThread);
    EXPECT_NE(cfg->h, nullptr);

    CloseHandle(cfg->fromMain[0]);
    CloseHandle(cfg->fromThread[0]);
    WaitForSingleObject(cfg->h, INFINITE);
    CloseHandle(cfg->h);
    delete cfg;
}

TEST_F(WorkerTest, MarkerThread) {
    int arr[10] = {0};
    Worker::Config* cfg = Worker::initThread(0, arr, 10, &cs, fromMain, fromThread);

    SetEvent(cfg->fromMain[0]);
    WaitForSingleObject(cfg->fromThread[0], INFINITE);

    bool marked = false;
    for (int i = 0; i < 10; i++) {
        if (arr[i] == cfg->num) {
            marked = true;
            break;
        }
    }
    EXPECT_TRUE(marked);
    
    cfg->flag = true;
    SetEvent(cfg->fromMain[0]);
    WaitForSingleObject(cfg->fromThread[0], INFINITE);

    CloseHandle(cfg->fromMain[0]);
    CloseHandle(cfg->fromThread[0]);
    CloseHandle(cfg->h);
    delete cfg;
}