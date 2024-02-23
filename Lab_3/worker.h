#include <iostream>
#include "windows.h"


class Worker {
public:
    struct Config {
        int num{};
        int *arr{};
        int arrSize{};
        bool flag = false;
        int marked_num = 0;
        CRITICAL_SECTION *cs{};
        HANDLE h{};
        HANDLE *fromMain{};
        HANDLE *fromThread{};
    };

    static Config *initThread(int num, int *arr, int arrSize,
                              CRITICAL_SECTION *cs,
                              HANDLE *fromMain, HANDLE *fromThread);

    static DWORD WINAPI marker(LPVOID v);
};