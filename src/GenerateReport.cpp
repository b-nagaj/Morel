#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>

#include "../lib/GenerateReport.hpp"
#include "../lib/Dialog.hpp"

GenerateReport::GenerateReport() {

    expenseListSize = 0;

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = 0;
    }

}

void GenerateReport::Generate() {

    Prompt();

    if (ValidatePath() && ValidateMonth()) {
        std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
        std::string yesNo;
        std:: cin >> yesNo;

        if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
            SetMonth(month);
            Calculate();
        }
        else {
            std::cout << generateReportDialog.errorMessage;
            generateReportDialog.Menu();
        }
    }
    else {
        std::cout << generateReportDialog.errorMessage;
    }

    generateReportDialog.option = 0;

}

void GenerateReport::Prompt() {

    std::cout << "\nGenerate A Report";

    std::cout << "\n\nWhere? (Include an absolute path): ";
    std::cin >> path;

    std::cout << "\nMonth: ";
    std::cin >> month;

}

bool GenerateReport::ValidatePath() {

    bool validPath = false;

    if (boost::filesystem::exists(path)) {
        validPath = true;
    }
    else {
        generateReportDialog.errorMessage = "\nERROR: The path you entered does not exist\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    return validPath;

}

bool GenerateReport::ValidateMonth() {

    bool validMonth = false;

    for (int i = 0; i < 24; i++) {
        if (validMonths[i] == month) {
            validMonth = true;
            break;
        }
    }

    if (validMonth == false) {
        generateReportDialog.errorMessage = "\nERROR: The month you entered is not a real month\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    return validMonth;

}

void GenerateReport::SetMonth(std::string m) {

    month = m;

}

void GenerateReport::Calculate() {

    reportFilename = path + month + "_2022_Report.txt";
    outputFile.open(reportFilename);

    std::cout << "\nCreating expense report...\n";

    Read();

    inputFile.open("expenseList.txt");
    if (inputFile) {
        for (int i = 0; i < 3; i++) {
            if (expenseNames[0] == "\n" || expenseNames[0] == "") {
                generateReportDialog.errorMessage = "\nERROR: Please update your expense list\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
                std::cout << generateReportDialog.errorMessage;
                break;
            }
            else if (expenseNames[i] == "end") {
                break;
            }
            else {
                expenses[i] = CalculateExpense(expenses[i], expenseNames[i]);
            }
        }

        std::cout << "\n\nDone! ✅\n\n"
                  << "<><><><><><><><><><><><><><>"; 

        Report();
        inputFile.close();
        outputFile.close(); 
    }
    else {
        generateReportDialog.errorMessage = "\nERROR: Please update your expense list\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
        std::cout << generateReportDialog.errorMessage;
    }

    ClearExpensesArray();

}

void GenerateReport::Read() {

    inputFile.open("expenseList.txt");

    for (int i = 0; i < 20; i++) {
        std::getline(inputFile, expenseNames[i], '\n');

        if (!inputFile.eof()) {
            expenseListSize += 1;
        }
    }
    
    inputFile.close();

}

double GenerateReport::CalculateExpense(double expenseType, std::string expenseName) {

    std::string expenseFilename = SetExpenseFilename(expenseName);

    std::ifstream inputFile;
    inputFile.open(expenseFilename);
    if (!inputFile) {
        std::cout << "\n" << expenseName << std::setw(27 - expenseName.length()) << " ❌";
    }
    else {
        ClearLinesArray();

        int index = 0;
        while (!inputFile.eof()) {
            std::getline(inputFile, lines[index]);
            expenseType += std::stod(lines[index]);
            index += 1;
        }

        inputFile.close();
        std::cout << "\n" << expenseName << std::setw(27 - expenseName.length()) << " ✅";
    }

    return expenseType;

}

std::string GenerateReport::SetExpenseFilename(std::string expenseName) {

    std::string expenseFilename = "/home/bryce/Documents/Monthly_Expenses/Data/" + month + "_2022/" + month + "_2022_" + expenseName + ".txt";
    return expenseFilename;

}

void GenerateReport::ClearLinesArray() {

    for (int i = 0; i < 20; i++) {
        lines[i] = "";
    }

}

void GenerateReport::Report() {

    generateReportDialog.ReportBanner(outputFile);
    outputFile << "\n";
    DisplayExpenses();
    outputFile << "\n\n\tTotal:" << std::setw(17) << "$" << std::fixed << std::setprecision(2) << GetTotal() << "\n";

}

void GenerateReport::DisplayExpenses() {

    for (int i = 0; i < expenseListSize - 1; i++) {

        if (expenseNames[i] == "end") {
            break;
        }
        else {
            outputFile << "\n\t" << expenseNames[i] << std::setw(23 - expenseNames[i].length()); 
            outputFile << std::fixed << std::setprecision(2) << "$" << expenses[i];
        }
    }

}

double GenerateReport::GetTotal() {

    double total;

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        total += expenses[i]; 
    }

    return total;

}

void GenerateReport::ClearExpensesArray() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = 0;
    }

    for (int i = 0; i < sizeof(expenseNames)/sizeof(expenseNames[0]); i++) {
        expenseNames[i] = "";
    }

}