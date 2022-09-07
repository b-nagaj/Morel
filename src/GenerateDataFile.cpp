#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>
#include <experimental/filesystem>

#include "../lib/GenerateDataFile.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"

GenerateDataFile::GenerateDataFile() {

    dataFilename = "";

}

void GenerateDataFile::Generate() {

    Prompt();

    if (ValidatePath() == true && ValidateMonth() == true) { 
        std::cout << "\nGenerate data files at " << "\"" << path << "\" for the month of " << month << "?" << "(Y/N) ";
        std::string yesNo;
        std:: cin >> yesNo;

        Read();

        if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes") {
            inputFile.open("expenseList.txt");

            if (inputFile) {
                for (int i = 0; i < generateDataFileReport.expenseListSize - 1; i++) {
                    if (generateDataFileReport.expenseNames[0] == "\n") {
                        generateDataFileDialog.errorMessage = "\nERROR: Please update your expenseList\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
                        std::cout << generateDataFileDialog.errorMessage;
                        break;
                    }
                    else if (generateDataFileReport.expenseNames[i] == "end") {
                        break;
                    }
                    else {
                        dataFilename = path + month + "_2022_" + generateDataFileReport.expenseNames[i] +".txt"; 
                        outfile.open(dataFilename);
                        outfile << "0";
                        outfile.close();
                        std::cout << "\n" << month << "_2022_" << generateDataFileReport.expenseNames[i] << ".txt" << " ✅";
                    }
                }
            }
        
            std::cout << "\n\nGenerated ✅\n\n<><><><><><><><><><><><><><>";
            inputFile.close();
        } 
    }
    else {
        std::cout << generateDataFileDialog.errorMessage;
    }

}

void GenerateDataFile::Prompt() {

    std::cout << "\nGenerate Data Files";

    std::cout << "\n\nWhere? (Include an absolute path): ";
    std::cin >> path;

    std::cout << "\nMonth: ";
    std::cin >> month;

}

void GenerateDataFile::Read() {

    inputFile.open("expenseList.txt");

    for (int i = 0; i < 20; i++) {
        std::getline(inputFile, generateDataFileReport.expenseNames[i], '\n');

        if (!inputFile.eof()) {
            generateDataFileReport.expenseListSize += 1;
        }
    }
    
    inputFile.close();

}

bool GenerateDataFile::ValidatePath() {

    bool validPath = false;

    if (boost::filesystem::exists(path)) {
        validPath = true;
    }
    else {
        generateDataFileDialog.errorMessage = "\nERROR: The path you entered does not exist\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    return validPath;

}

bool GenerateDataFile::ValidateMonth() {

    bool validMonth = false;

    for (int i = 0; i < 24; i++) {
        if (generateDataFileReport.validMonths[i] == month) {
            validMonth = true;
            break;
        }
    }

    if (validMonth == false) {
        generateDataFileDialog.errorMessage = "\nERROR: The month you entered is not a real month\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    return validMonth;

}
