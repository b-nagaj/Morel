#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>

#include "../lib/Calculator.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"

void Calculator::Prompt() {

    Dialog myDialog;
    myDialog.WelcomeBanner();
    
    while (myDialog.option != 6) {
        myDialog.Menu();

        switch (myDialog.option) {
        case 1 :
            GenerateAReport();
            break;

        case 2 : 
            std::cout << "\nView A Report";
            break;
        
        case 3 :
            std::cout << "\nUpdate A Report";
            break;
        
        case 4 :
            std::cout << "\nUpdate An Expense";
            break;
        
        case 5 :
            std::cout << "\nHelp";
            break;
        
        case 6 :
            std::cout << "\nQuitting!\n\n";
            break;
        }
    }

}

void Calculator::GenerateAReport() {

    Dialog myDialog;

    std::cout << "\nGenerate A Report";
    std::cout << "\n\nMonth: ";
    std::string month;
    std::cin >> month;

    std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
    std::string yesNo;
    std:: cin >> yesNo;

    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
        GenerateReport myReport;
        myReport.SetMonth(month);
        myReport.Calculate();
    }
    else {
        myDialog.Menu();
    }

}