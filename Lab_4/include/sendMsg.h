#ifndef SENDMSG_H
#define SENDMSG_H

#include <string>
#include <fstream>
#include "windows.h"

void sendMsg(const std::string& message, const std::string& binFileName, std::ofstream& binOutputStream, int MESSAGE_LENGTH, char* messageCharset, HANDLE hReadAccessSemaphore);

#endif //SENDMSG_H
