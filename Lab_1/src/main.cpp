#include <windows.h>
#include <iostream>
#include <fstream>
#include "employee.h"
#include <conio.h>
#include <string>

const int maxCharLength = 256;
const int maxBufferCapacity = 1000;
const char creatorExeFileName[] = "creator.exe";
const char reporterExeFileName[] = "reporter.exe";

void startProcess(char* buffer) {
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	if (!CreateProcess(
            NULL, buffer,
            NULL, NULL,
            FALSE, CREATE_NEW_CONSOLE,
            NULL, NULL,
            &si, &pi))
	{
		std::cout << "\nERROR: Unable to open process\n";
		std::cout << "Press any key to exit...";
		system("pause");
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

int main()
{
	char binaryFileName[maxCharLength];

	std::cout << "Enter binary file name: ";
	std::cin.getline(binaryFileName, maxCharLength);

	int recAmount = 0;
	std::cout << "Enter the number of records: ";
	std::cin >> recAmount;
	std::cin.ignore();

	char buffer[maxBufferCapacity];
	sprintf_s(buffer, "%s %s %d",creatorExeFileName,
            binaryFileName, recAmount);
	startProcess(buffer);

	std::cout << "Information in binary file:";
	std::ifstream fin(binaryFileName, std::ios::binary);
	fin.read((char *)&recAmount, sizeof(int));
	auto* records = new employee[recAmount];

	for (int i = 0; i < recAmount; i++)
	{
		fin.read((char *)&records[i], sizeof(employee));
	}

	for (int i = 0; i < recAmount; i++)
	{
		std::cout << "\n" << records[i].ID << " " << records[i].name << " " << records[i].hours;
	}

	delete[] records;
	fin.close();

	char outputFileName[maxCharLength];
	std::cout << "\nEnter output file name: ";
	std::cin.getline(outputFileName, maxCharLength);
	double salaryHour = 0.0;
	std::cout << "Enter salary value per one hour: ";
	std::cin >> salaryHour;

	buffer[0] = '\0';
	sprintf_s(
            buffer, "%s %s %s %lf", reporterExeFileName,
              binaryFileName, outputFileName, salaryHour);
	startProcess(buffer);

	std::ifstream finReportInfo(outputFileName);

	std::cout << "\nInformation in output file:" << "\n";
	char str[maxBufferCapacity];
	for (int i = 0; i < recAmount; i++)
	{
		finReportInfo.getline(str, maxBufferCapacity);
		for (int i = 0; str[i] != '\0'; i++)
			printf("%c", str[i]);
		std::cout << "\n";
	}
	finReportInfo.close();
	return 0;
}