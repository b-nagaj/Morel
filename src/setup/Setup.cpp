#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <filesystem>
#include <boost/filesystem.hpp>

#include "Setup.hpp"

Setup::Setup() {

    username = "";
    dataFilesPath = "./data/";
    reportFilesPath = "./reports/";

    for (int i = 0; i < 20; i++) {
        expenses[i] = "";
    }

    expense = "";
    numExpenses = 0;

    if (!std::filesystem::exists("config.txt")) {
        WelcomeBanner();
        BeginSetup();
    }

}

void Setup::BeginSetup() {

    GetUsername();
    GetExpenseList();
    Write();

}

void Setup::WelcomeBanner() {

    std::cout << " __  __                _" 
                << "\n|  \\/  | ___  _ __ ___| |"
                << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
                << "\n| |  | | (_) | | |  __/ |"
                << "\n|_|  |_|\\___/|_|  \\___|_|";

    std::cout << "\n\nSetup";

}

void Setup::GetUsername() {

    std::cout << "\n\nUsername: ";
    std::getline(std::cin, username);

}

void Setup::GetExpenseList() {

    std::cout << "\nPlease give a list of up to 20 expenses"
                << "\nInclude each expense on a seperate line"
                << "\nType 'end' to indicate the end of the list\n\n";

    while (expense != "end" && numExpenses < 20) {
        std::cout << "Expense" << "[" << (numExpenses + 1) << "]: ";
        std::getline(std::cin, expense);
        expenses[numExpenses] = expense;
        numExpenses++;
    }
    numExpenses--;

}

void Setup::Write() {

    outputFile.open("config.txt");

    if(outputFile) {
        outputFile << username << std::endl
                    << dataFilesPath << std::endl
                    << reportFilesPath << std::endl;
        
        for (int i = 0; i < numExpenses; i++) {
            outputFile << expenses[i] << std::endl;
        }

        std::cout << "\nSetup Passed ✅\n";
    }
    else {
        std::cout << "\nSetup Failed ❌\n";
    }

    outputFile.close();

}
