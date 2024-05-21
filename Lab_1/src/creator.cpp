#include <iostream>
#include <fstream>
#include "employee.h"

void getRecord(employee* record, int i, std::istream& input, std::ostream& output) {
    output << "Employee " << (i + 1) << ":\n";
    output << "Enter ID: ";
    input >> record->ID;
    output << "\n";
    output << "Enter name: ";
    input >> record->name;
    output << "\n";
    output << "Enter hours: ";
    input >> record->hours;
    output << "\n";
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