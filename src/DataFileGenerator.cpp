#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>
#include <experimental/filesystem>

#include "../lib/DataFileGenerator.hpp"

DataFileGenerator::DataFileGenerator() {

    for (int i = 0; i < (sizeof(expenses) / sizeof(expenses[0])); i++) {
        expenses[i] = "";
    }
    for (int i = 0; i < (sizeof(lines) / sizeof(lines[i])); i++) {
        lines[i] = "";
    }

    expense = "";
    numExpenses = 0;
    month = "";
    dataFilesPath = "";
    dataFilename = "";

}

void DataFileGenerator::Generate() {

    std::cout << "\nGenerate Data Files";

    GetMonth();
    GetPaths();
    GetExpenses();

    std::cout << "\nGenerate data files for the month of " << month << "?" << "(Y/N) ";
        std::string yesNo;
        std:: cin >> yesNo;
    
    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes") {
        for (int i = 0; i < numExpenses; i++) {
                dataFilename = dataFilesPath + month + "_" + expenses[i] + ".txt";
                outputFile.open(dataFilename);
                outputFile << "0.00";
                outputFile.close();
                std::cout << "\n" << month << "_" << expenses[i] << ".txt" << std::setw(21 - (expenses[i] + ".txt").length()) << " ✅"; 
            }
            std::cout << "\n\nGenerated" << std::setw(20) << " ✅" << "\n\n<><><><><><><><><><><><><><>";
    } 
    else {
        std::cout << "\nGenerated " <<  std::setw(20) << " ❌" << "\n\n<><><><><><><><><><><><><><>";
    }

    numExpenses = 0;
}

void DataFileGenerator::GetMonth() {

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    if (!ValidateMonth()) {
        GetMonth();
    }

}
