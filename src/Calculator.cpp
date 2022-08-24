#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>

#include "../lib/Calculator.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"

void Calculator::Prompt() {

    std::cout << " __  __                _" 
              << "\n|  \\/  | ___  _ __ ___| |"
              << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n| |  | | (_) | | |  __/ |"
              << "\n|_|  |_|\\___/|_|  \\___|_|";
    
    Dialog myDialog;
    
    while (option != 6) {
        option = myDialog.Menu();

        switch (option) {
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
    std::cin >> month;

    std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
    std:: cin >> choice;

    if (choice == "Y" || choice == "Yes" || choice == "y" || choice == "yes"){
        GenerateReport myReport;
        myReport.SetMonth(month);
        myReport.Calculate();
    }
    else {
        myDialog.Menu();
    }

}