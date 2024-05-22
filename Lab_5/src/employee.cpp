#include "employee.h"

int generateCountOfClient() {
    srand(time(0));
    return (rand() / 5 + 3) % 5 + 2;
}

employee *findEmp(const int ID) {
    employee key;
    key.num = ID;
    return (employee *) bsearch(&key, emps,
                                empCount, employeeSize, empCmp);
}

void sortEmps() {
    qsort(emps, empCount, employeeSize, empCmp);
}

void writeData(std::string fileName) {
    std::fstream fin(fileName.c_str(), std::ios::out | std::ios::binary);
    fin.write(reinterpret_cast<const char *>(emps), employeeSize * empCount);

    std::cout << "Data has been writing.\n";
    fin.close();
}

void readDataSTD() {
    emps = new employee[empCount];

    std::cout << "Input ID, name and working hours of each employee: ";
    for (int i = 0; i < empCount; ++i) {
        std::cout << "¹" << i + 1 << ": ";
        std::cin >> emps[i].num >> emps[i].name >> emps[i].hours;
    }
}