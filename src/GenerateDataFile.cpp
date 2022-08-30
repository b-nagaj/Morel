#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <algorithm>
#include <vector>

#include "../lib/GenerateDataFile.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"

GenerateDataFile::GenerateDataFile() {

    dataFilename = "";
    dataFilenamePath = "";

}

void GenerateDataFile::Prompt() {

    std::cout << "\nGenerate Data Files";

    std::cout << "\n\nWhere? (Include an absolute path): ";
    std::cin >> path;

    std::cout << "\nMonth: ";
    std::cin >> month;

}

void GenerateDataFile::Generate() {

    Dialog GenerateDataFilesDialog;
    GenerateReport myReport2;

    Prompt();

    bool validMonth = false;
    for (int i = 0; i < 24; i++) {
        if (myReport2.validMonths[i] == month) {
            validMonth = true;
            break;
        }
    }

    if (validMonth) { 
        std::cout << "\nGenerate data files at " << "\"" << path << "\" for the month of " << month << "?" << "(Y/N) ";
        std::string yesNo;
        std:: cin >> yesNo;

        if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
            for (int i = 0; (i < sizeof(myReport2.expenseNames) / sizeof(myReport2.expenseNames[0])); i++) {
                dataFilename = month + "_2022_" + myReport2.expenseNames[i] + ".txt"; 
                std::ofstream outfile;
                dataFilenamePath = path + "/" + dataFilename;
                outfile.open(dataFilenamePath);
                outfile.close();
            }

            std::cout << "\nGenerated" << " ✅"
                      << "\n\n<><><><><><><><><><><><><><>"; 
        }
        else {
            GenerateDataFilesDialog.Menu();
        }    
    }
    else {
        GenerateDataFilesDialog.errorMessage = "\nERROR: The value you entered is not a real month";
        std::cout << GenerateDataFilesDialog.errorMessage;
    }

}