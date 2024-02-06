#include <fstream>
#include "employee.h"

int main(int argc, char *argv[])
{
    std::ifstream fin(argv[1], std::ios::binary);
    std::ofstream fout(argv[2]);
    double salaryHour = atof(argv[3]);

    int recAmount;
    fin.read((char *)&recAmount, sizeof(int));
    auto* records = new employee[recAmount];

    for (int i = 0; i < recAmount; i++)
    {
        fin.read((char *)&records[i], sizeof(employee));
    }

    for (int i = 0; i < recAmount; i++)
    {
        fout << "ID: " << records[i].ID <<
             "\tName: " << records[i].name <<
             "\tHours: " << records[i].hours <<
             "\tSalary: " << records[i].hours * salaryHour << "\n";
    }
    fin.close();
    fout.close();

    delete[] records;

    return 0;
}