#ifndef LAB_2_C__11__PARAMETERS_H
#define LAB_2_C__11__PARAMETERS_H

#include <vector>
#include <iostream>

struct minMaxParameters {
    std::vector <int>* nums;
    int* minValue;
    int* maxValue;
};

struct sumParameters {
    std::vector<int>* nums;
    double* average;
};

const int compareSleepDuration = 70;
const int sumSleepDuration = 12;

DWORD WINAPI min_max(LPVOID lpParam);

DWORD WINAPI average(LPVOID lpParam);

std::vector<double> updateArray(const std::vector <int>& nums, int minValue, int maxValue, double avg);

#endif //LAB_2_C__11__PARAMETERS_H
