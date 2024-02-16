#include <windows.h>
#include "parameters.h"
#include <iostream>
#include <vector>

const int compareSleepDuration = 70;
const int sumSleepDuration = 12;

DWORD WINAPI min_max(LPVOID lpParam)
{
    auto* params = (minMaxParameters*)lpParam;

    if (!params->minValue) {
        printf("Invalid pointer to minValue\n");
        return 1;
    }
    if (!params->maxValue) {
        printf("Invalid pointer to maxValue\n");
        return 1;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (int num : *params->nums) {
        if (num < min_val) {
            min_val = num;
        }
        Sleep(compareSleepDuration);
        if (num > max_val) {
            max_val = num;
        }
        Sleep(compareSleepDuration);
    }

    *params->minValue = min_val;
    *params->maxValue = max_val;

    printf("Min value: %d\nMax value: %d\n", min_val, max_val);

    return 0;
}

DWORD WINAPI average(LPVOID lpParam)
{
    auto* params = (sumParameters*)lpParam;

    if (!params->average) {
        printf("Invalid pointer to average\n");
        return 1;
    }

    double sum = 0;

    for (int num : *params->nums) {
        sum += num;
        Sleep(sumSleepDuration);
    }

    *params->average = sum / (double)params->nums->size();

    printf("Average: %.3lf\n", *params->average);

    return 0;
}

std::vector<double> updateArray(const std::vector <int>& nums, int minValue, int maxValue, double avg) {
    std::vector<double> newArr;
    newArr.reserve(nums.size());

    for (int num : nums) {
        if (num == minValue || num == maxValue) {
            newArr.push_back(avg);
        } else {
            newArr.push_back(num);
        }
    }

    return newArr;
}

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