#include "sendMsg.h"

void sendMsg(const std::string& message, const std::string& binFileName, std::ofstream& binOutputStream, int MESSAGE_LENGTH, char* messageCharset, HANDLE hReadAccessSemaphore) {
    for (std::size_t i = 0; i < MESSAGE_LENGTH; i++)
        messageCharset[i] = '_';
    message.copy(messageCharset, message.length());
    binOutputStream.open(binFileName, std::ios::binary | std::ios::app);
    binOutputStream.write((char*)&messageCharset, sizeof(messageCharset));
    binOutputStream.close();
    ReleaseSemaphore(hReadAccessSemaphore, 1, nullptr);
}
