#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>

#include "../lib/GenerateReport.hpp"
#include "../lib/Dialog.hpp"

GenerateReport::GenerateReport() {

    numExpenses = 0;

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = 0;
    }

}

void GenerateReport::Generate() {

    Prompt();

    std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
    std::string yesNo;
    std:: cin >> yesNo;

    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
        Calculate();
    }
    else {
        std::cout << "\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    Report();
    inputFile.close();
    outputFile.close(); 
    ClearExpenseArrays();
    numExpenses = 0;

    std::cout << "\n\nGenerated ✅\n\n"
              << "<><><><><><><><><><><><><><>";

}

void GenerateReport::Prompt() {

    std::cout << "\nGenerate A Report";

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    if (!ValidateMonth()) {
        Prompt();
    }

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
        std::cout << "\nERROR: The month you entered is not a real month\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    return validMonth;

}

void GenerateReport::Calculate() {

    reportFilename = "/home/bryce/Documents/Monthly_Expenses/Reports/" + month + "/" + month + "_Report.txt";
    outputFile.open(reportFilename);

    std::cout << "\nCreating expense report...\n";

    GetPath();
    GetExpenses();

    for (int i = 0; i < numExpenses; i++) {
        expenses[i] = CalculateExpense(expenses[i], expenseNames[i]);
    } 

}

void GenerateReport::GetPath() {

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

    if (lines[2].back() != '/') {
        reportFilesPath = lines[1] + "/";
    }
    else {
        reportFilesPath = lines[1];
    }
    
    inputFile.close();

}

void GenerateReport::GetExpenses() {

    inputFile.open("config.txt");

    for (int i = 0; i < 3; i++) {
        std::getline(inputFile, expenseName);
    }

    if (inputFile) {
        while (expenseName != "" && numExpenses < 20) {
            std::getline(inputFile, expenseName);
            expenseNames[numExpenses] = expenseName;
            numExpenses++;
        }
        numExpenses--;
    }

    inputFile.close();

}

double GenerateReport::CalculateExpense(double expenseType, std::string expenseName) {

    expenseFilename = dataFilesPath + month + "/" + month + "_" + expenseName + ".txt"; 

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

    for (int i = 0; i < numExpenses; i++) {
        outputFile << "\n\t" << expenseNames[i] << std::setw(23 - expenseNames[i].length()); 
        outputFile << std::fixed << std::setprecision(2) << "$" << expenses[i];
    }

}

double GenerateReport::GetTotal() {

    double total;

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        total += expenses[i]; 
    }

    return total;

}

void GenerateReport::ClearExpenseArrays() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = 0;
    }

    for (int i = 0; i < sizeof(expenseNames)/sizeof(expenseNames[0]); i++) {
        expenseNames[i] = "";
    }

}