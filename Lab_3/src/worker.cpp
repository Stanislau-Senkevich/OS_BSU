#include "worker.h"

Worker::Config *Worker::initThread(int num, int *arr, int arrSize,
                                   CRITICAL_SECTION *cs,
                                   HANDLE *fromMain, HANDLE *fromThread) {
    auto cfg = new Worker::Config;
    fromMain[num] = CreateEvent(NULL, TRUE, FALSE, NULL);
    fromThread[num] = CreateEvent(NULL, TRUE, FALSE, NULL);
    cfg->num = num + 1;
    cfg->arrSize = arrSize;
    cfg->arr = arr;
    cfg->cs = cs;
    cfg->fromMain = fromMain;
    cfg->fromThread = fromThread;

    cfg->h = CreateThread(
            NULL, 0,
            Worker::marker, (LPVOID) cfg,
            0, NULL
    );

    return cfg;
}


DWORD WINAPI Worker::marker(LPVOID v) {
    auto cfg = (Config *) v;

    EnterCriticalSection(cfg->cs);
    srand(cfg->num);

    bool *marked = new bool[cfg->arrSize];
    for (int i = 0; i < cfg->arrSize; i++) {
        marked[i] = false;
    }
    LeaveCriticalSection(cfg->cs);

    while (true) {
        int num = rand();
        num %= (cfg->arrSize);
        EnterCriticalSection(cfg->cs);
        if (cfg->arr[num] == 0) {
            Sleep(5);
            cfg->arr[num] = cfg->num;
            marked[num] = true;
            cfg->marked_num++;
            LeaveCriticalSection(cfg->cs);
            Sleep(5);
            continue;
        }

        printf("\nMarker #%d\nCan't modify the element with index: %d\nNumber of marked elements: %d\n\n",
               cfg->num, num, cfg->marked_num);
        LeaveCriticalSection(cfg->cs);

        SetEvent(cfg->fromThread[cfg->num - 1]);
        WaitForSingleObject(cfg->fromMain[cfg->num - 1], INFINITE);
        ResetEvent(cfg->fromThread[cfg->num - 1]);
        ResetEvent(cfg->fromMain[cfg->num - 1]);
        WaitForSingleObject(cfg->fromMain[cfg->num - 1], INFINITE);


        if (cfg->flag) {
            EnterCriticalSection(cfg->cs);
            for (int i = 0; i < cfg->arrSize; i++) {
                if (marked[i]) {
                    cfg->arr[i] = 0;
                }
            }
            cfg->marked_num = 0;
            LeaveCriticalSection(cfg->cs);
            break;

        }
    }
    delete[] marked;

    SetEvent(cfg->fromThread[cfg->num - 1]);

    EnterCriticalSection(cfg->cs);
    printf("Thread #%d is finished\n", cfg->num);
    LeaveCriticalSection(cfg->cs);
    return 0;
}