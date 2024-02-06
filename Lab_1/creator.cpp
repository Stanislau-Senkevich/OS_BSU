#include <iostream>
#include <fstream>
#include "employee.h"

void getRecord(employee* record, int i) {
    std::cout << "Employee " << (i + 1) << ":\n";
    std::cout << "Enter ID: ";
    std::cin >> record->ID;
    std::cout << "\n";
    std::cout << "Enter name: ";
    std::cin >> record->name;
    std::cout << "\n";
    std::cout << "Enter hours: ";
    std::cin >> record->hours;
    std::cout << "\n";
}

int main(int argc, char* argv[])
{
    std::ofstream fout(argv[1], std::ios::binary);

    int recAmount = atoi(argv[2]);
    auto* records = new employee[recAmount];

    std::cout << "\nType information about " << recAmount << " employees:\n";
    for (int i = 0; i < recAmount; i++)
    {
        getRecord(&records[i], i);
    }

    fout.write((char*)&recAmount, sizeof(int));
    for (int i = 0; i < recAmount; i++) {
        fout.write((char*)&records[i], sizeof(employee));
    }

    fout.close();

    delete[] records;

    return 0;
}