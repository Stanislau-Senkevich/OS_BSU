#include <iostream>
#include <windows.h>
#include "worker.h"

HANDLE *fromMain;
HANDLE *fromThread;
int *arr;
int arrSize, threadNum;
CRITICAL_SECTION cs;


void printArray() {
    for (int i = 0; i < arrSize; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}


int main() {
    std::cout << "Array size: " << "\n";
    std::cin >> arrSize;

    arr = new int[arrSize];
    for (int i = 0; i < arrSize; i++) {
        arr[i] = 0;
    }

    std::cout << "Thread number: \n";
    std::cin >> threadNum;
    auto **configs = new Worker::Config *[threadNum];
    InitializeCriticalSection(&cs);

    fromMain = new HANDLE[threadNum];
    fromThread = new HANDLE[threadNum];
    for (int i = 0; i < threadNum; i++) {
        configs[i] = Worker::initThread(i + 1, arr, arrSize, &cs, fromMain, fromThread);

    }

    int numToStop;
    for (int i = 0; i < threadNum; i++) {
        WaitForMultipleObjects(threadNum, fromThread, TRUE, INFINITE);
        for (int j = 0; j < threadNum; j++) {
            SetEvent(fromMain[j]);
        }

        EnterCriticalSection(&cs);
        printArray();
        do {
            std::cout << "Enter the num of thread to stop: ";
            std::cin >> numToStop;
            if (numToStop < 1 || numToStop > threadNum) {
                std::cout << "Invalid thread num\n";
                continue;
            }
            if (configs[numToStop - 1]->flag) {
                std::cout << "This thread is already finished\n";
            }
        } while (configs[numToStop - 1]->flag);

        configs[numToStop - 1]->flag = true;
        LeaveCriticalSection(&cs);

        SetEvent(fromMain[numToStop - 1]);
        WaitForSingleObject(fromThread[numToStop - 1], INFINITE);


        for (int j = 0; j < threadNum; j++) {
            SetEvent(fromMain[j]);
            ResetEvent(fromMain[j]);
        }
    }

    std::cout << "All threads are finished\n";
    for (int i = 0; i < threadNum; i++) {
        CloseHandle(configs[i]->h);
        CloseHandle(fromThread[i]);
        CloseHandle(fromMain[i]);
    }

    for (int i = 0; i < threadNum; i++) {
        delete[] configs[i];
    }

    delete[] configs;
    delete[] fromThread;
    delete[] fromMain;
    DeleteCriticalSection(&cs);
    delete[] arr;
    return 0;

}