#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>
#include <experimental/filesystem>

#include "../lib/GenerateDataFile.hpp"

GenerateDataFile::GenerateDataFile() {

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

void GenerateDataFile::Generate() {

    Prompt();
    GetPath();
    GetExpenses();

    std::cout << "\nGenerate data files for the month of " << month << "?" << "(Y/N) ";
        std::string yesNo;
        std:: cin >> yesNo;
    
    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes") {
        for (int i = 0; i < numExpenses; i++) {
                dataFilename = dataFilesPath + month + "/" + month + "_" + expenses[i] + ".txt";
                outFile.open(dataFilename);
                outFile << "0";
                outFile.close();
                std::cout << "\n" << month << "_2022_" << expenses[i] << ".txt" << " ✅";
            }
            std::cout << "\n\nGenerated ✅\n\n<><><><><><><><><><><><><><>";
    } 
    else {
        std::cout << "\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    numExpenses = 0;
}

void GenerateDataFile::Prompt() {

    std::cout << "\nGenerate Data Files";

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    if (!ValidateMonth()) {
        Prompt();
    }

}

bool GenerateDataFile::ValidateMonth() {

    bool validMonth = false;

    for (int i = 0; i < 24; i++) {
        if (validMonths[i] == month) {
            validMonth = true;
            break;
        }
    }

    if (validMonth == false) {
        std::cout << "\nERROR: The month you entered is not a real month\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    return validMonth;

}

void GenerateDataFile::GetPath() {

    inputFile.open("config.txt");

    int i = 0;
    while (i < 3) {
        std::getline(inputFile, lines[i], '\n');
        i++;
    }

    if (lines[1].back() != '/') {
        dataFilesPath = lines[1] + "/";
    }
    else {
        dataFilesPath = lines[1];
    }
    
    inputFile.close();

}

void GenerateDataFile::GetExpenses() {

    inputFile.open("config.txt");

    for (int i = 0; i < 3; i++) {
        std::getline(inputFile, expense);
    }

    if (inputFile) {
        while (expense != "" && numExpenses < 20) {
            std::getline(inputFile, expense);
            expenses[numExpenses] = expense;
            numExpenses++;
        }
        numExpenses--;
    }

    inputFile.close();

}