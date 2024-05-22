#include <windows.h>
#include "../include/parameters.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> nums;
    int n, num;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        nums.push_back(num);
    }

    minMaxParameters minMaxParams = {&nums, new int, new int};
    sumParameters sumParams = {&nums, new double};

    HANDLE hMinMax = CreateThread(
            NULL,0,
            min_max, &minMaxParams,
            0, NULL);
    if (hMinMax == NULL) {
        printf("Failed to create min_max thread\n");
        return 1;
    }

    HANDLE hAverage = CreateThread(
            NULL, 0,
            average, &sumParams,
            0, NULL);
    if (hAverage == NULL) {
        printf("Failed to create average thread");
        CloseHandle(hMinMax);
        return 1;
    }

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    auto newArr = updateArray(
            nums, *minMaxParams.minValue,
            *minMaxParams.maxValue, *sumParams.average);

    printf("Old array:");
    for (int i : nums) {
        printf(" %d", i);
    }
    printf("\nUpdated array:");
    for (double i : newArr) {
        printf(" %.3lf", i);
    }

    CloseHandle(hMinMax);
    CloseHandle(hAverage);
    return 0;
}