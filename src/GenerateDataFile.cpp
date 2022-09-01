#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>

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

        if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
            for (int i = 0; (i < sizeof(generateDataFileReport.expenseNames) / sizeof(generateDataFileReport.expenseNames[0])); i++) {
                dataFilename = path + month + "_2022_" + generateDataFileReport.expenseNames[i] + ".txt"; 
                std::ofstream outfile;
                outfile.open(dataFilename);
                outfile.close();
            }

            std::cout << "\nGenerated" << " ✅"
                      << "\n\n<><><><><><><><><><><><><><>"; 
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
