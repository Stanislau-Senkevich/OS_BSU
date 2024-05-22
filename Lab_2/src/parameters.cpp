#include "../include/parameters.h"

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
