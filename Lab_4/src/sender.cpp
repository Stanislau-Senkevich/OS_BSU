#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include "sendMsg.h"

int main(int argc, char* argv[]) {
    std::ofstream   binOutputStream;
    std::string     binFileName{ argv[1] };
    std::string     message;
    char            messageCharset[20]{    };
    const int       MESSAGE_LENGTH{ 20 };
    int             option{ 0 };
    int             processId{std::stoi(argv[2]) };
    HANDLE          hReadAccessSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Read Access Semaphore");
    HANDLE          hWriteAccessSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Write Access Semaphore");
    HANDLE          hCurrentProcess = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Current Process Owner2");
    HANDLE          senderStartEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, "START PROCESS" + processId);

    SetEvent(senderStartEvent);
    std::cout << "You are currently in Sender.exe number " << processId << " process \n" << std::endl;

    while (option != 2) {
        WaitForSingleObject(hWriteAccessSemaphore, INFINITE);
        WaitForSingleObject(hCurrentProcess, INFINITE);
        std::cout << "Options: \n" <<
                  "1. Write messages " + binFileName + " (max. message length is 20 characters) \n" <<
                  "2. Exit program \n";
        std::cin >> option;
        switch (option) {
            case 1:
                option = 0;
                sendMsg(message, binFileName, binOutputStream, MESSAGE_LENGTH, messageCharset, &hReadAccessSemaphore);
                break;
            case 2:
                std::cout << "Exiting process..." << std::endl;
                ReleaseMutex(hCurrentProcess);
                Sleep(500);
                break;
            default:
                std::cout << "Invalid option\n";
                continue;
        }
    }
    return 0;
}