#include "sendMsg.h"
#include <gtest/gtest.h>
#include <fstream>
#include <windows.h>

class SendMsgTest : public ::testing::Test {
protected:
    const int MESSAGE_LENGTH = 20;
    char messageCharset[20]{};
    HANDLE hSemaphore{};

    void SetUp() override {
        memset(messageCharset, '_', MESSAGE_LENGTH);

        hSemaphore = CreateSemaphore(nullptr, 0, 1, nullptr);
        ASSERT_TRUE(hSemaphore != nullptr);
    }

    void TearDown() override {
        CloseHandle(hSemaphore);
    }
};

TEST_F(SendMsgTest, TestSendMsg) {
    std::string testMessage = "Hello";
    std::string binFileName = "test.bin";
    std::ofstream binOutputStream;

    sendMsg(testMessage, binFileName, binOutputStream, MESSAGE_LENGTH, messageCharset, hSemaphore);

    ASSERT_EQ(std::string(messageCharset, MESSAGE_LENGTH), "Hello_______________");

    std::ifstream binInputStream(binFileName, std::ios::binary);
    ASSERT_TRUE(binInputStream.is_open());

    char readBuffer[20];
    binInputStream.read(readBuffer, sizeof(readBuffer));
    binInputStream.close();

    ASSERT_EQ(std::string(readBuffer, MESSAGE_LENGTH), "Hello_______________");

    DWORD waitResult = WaitForSingleObject(hSemaphore, 0);
    ASSERT_EQ(waitResult, WAIT_OBJECT_0);

    std::remove(binFileName.c_str());
}
