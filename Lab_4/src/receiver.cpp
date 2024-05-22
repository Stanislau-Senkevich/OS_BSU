#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"

int main() {
    STARTUPINFO si{0};
    PROCESS_INFORMATION pi{nullptr};
    std::ifstream binInputStream;
    std::string binFileName;
    std::string strCmdLineRequest;
    LPSTR lpwCmdLineRequest;
    HANDLE *hProcesses;
    HANDLE *hStartEvents;
    HANDLE hCurrentProcess;
    HANDLE hReadAccessSemaphore;
    HANDLE hWriteAccessSemaphore;
    DWORD response;
    const short DELAY{25000};
    const short messageLength{20};
    char message[20]{};
    int numberOfProcesses{0};
    int numberOfEntries{0};
    int bytesRead{0};
    int option{0};


    std::cout << "Input .bin file name: ";
    std::cin >> binFileName;
    std::cout << "Input number of entries: ";
    std::cin >> numberOfEntries;
    std::cout << "Input number of Sender processes: ";
    std::cin >> numberOfProcesses;

    hCurrentProcess = CreateMutex(nullptr, TRUE, "Current Process Owner");
    hReadAccessSemaphore = CreateSemaphore(nullptr, 0, numberOfEntries, "Read Access Semaphore");
    hWriteAccessSemaphore = CreateSemaphore(nullptr, numberOfEntries, numberOfEntries, "Write Access Semaphore");

    hProcesses = new HANDLE[numberOfProcesses];
    hStartEvents = new HANDLE[numberOfProcesses];
    for (int i = 0; i < numberOfProcesses; i++) {
        char *num;
        sprintf(num, "START PROCESS %d", i);
        hStartEvents[i] = CreateEvent(nullptr, TRUE, FALSE, (LPCSTR) (num));
    }


    for (std::size_t i = 0; i < numberOfProcesses; i++) {
        strCmdLineRequest = std::string("Sender.exe") + " " + binFileName + " " + std::to_string(i);
        lpwCmdLineRequest = &strCmdLineRequest[0];
        if (!CreateProcess(nullptr, lpwCmdLineRequest, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr, nullptr,
                           &si, &pi))
            std::cout << "Unable to create \"Sender.exe\" process" << std::endl;
        CloseHandle(pi.hThread);
        hProcesses[i] = pi.hProcess;
    }

    WaitForMultipleObjects(numberOfProcesses, hStartEvents, TRUE, INFINITE);
    ReleaseMutex(hCurrentProcess);
    while (option != 2) {
        WaitForSingleObject(hCurrentProcess, INFINITE);
        response = WaitForSingleObject(hReadAccessSemaphore, DELAY);
        if (response == WAIT_TIMEOUT) {
            std::cout << "[warning] Timeout: no response!" << std::endl;
            break;
        }
        std::cout << "Options: \n" <<
                  "1. Read " + binFileName + '\n' <<
                  "2. Exit program \n";
        std::cin >> option;
        switch (option) {
            case 1:
                option = 0;
                binInputStream.open(binFileName, std::ios::binary);
                binInputStream.seekg(bytesRead);
                if (binInputStream.tellg() != 0 || !binInputStream.eof()) {
                    binInputStream.read((char *) &message, sizeof(message));
                    std::cout << "Message: ";
                    for (char i: message)
                        std::cout << i;
                    std::cout << std::endl;
                    binInputStream.close();
                    bytesRead += messageLength;
                    ReleaseSemaphore(hWriteAccessSemaphore, 1, nullptr);
                } else
                    continue;
                break;
            case 2:
                std::cout << "Exiting process..." << std::endl;
                Sleep(500);
                break;
            default:
                std::cout << "Invalid option\n";
                continue;
        }
    }

    CloseHandle(hCurrentProcess);
    CloseHandle(hReadAccessSemaphore);
    CloseHandle(hWriteAccessSemaphore);

    for (std::size_t i = 0; i < numberOfProcesses; i++)
        CloseHandle(hStartEvents[i]);
    delete[] hStartEvents;

    for (std::size_t i = 0; i < numberOfProcesses; i++)
        CloseHandle(hProcesses[i]);
    delete[] hProcesses;

    return 0;
}
