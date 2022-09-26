#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <boost/filesystem.hpp>

#include "../lib/Setup.hpp"

Setup::Setup() {

    for (int i = 0; i < 20; i++) {
        expenses[i] = "";
    }

    expense = "";
    numExpenses = 0;
    username = "";
    dataFilesPath = "";
    reportFilesPath = "";

    WelcomeBanner();

}

void Setup::BeginSetup() {

    GetUsername();
    GetPaths();

    if (ValidatePaths()) {
        GetExpenseList();
        Write();
    }
    else {
        while (!ValidatePaths()) {
            GetPaths();
        }

        GetExpenseList();
        Write();
    }

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
    std::cin >> username;

}

void Setup::GetPaths() {

    std::cout << "\nPath to store data files (include an absolute path): ";
    std::cin >> dataFilesPath;

    std::cout << "\nPath to store report files (include an absolute path): ";
    std::cin >> reportFilesPath;

}

bool Setup::ValidatePaths() {

    bool validPath = false;

    if (boost::filesystem::exists(dataFilesPath) && boost::filesystem::exists(reportFilesPath)) {
        validPath = true;
    }
    else {
        std::cout << "\nERROR: The path(s) you entered does not exist\n";
    }

    return validPath;

}

void Setup::GetExpenseList() {

    std::cout << "\nPlease give a list of up to 20 expenses"
                << "\nInclude each expense on a seperate line"
                << "\nType 'end' to indicate the end of the list\n\n";

    while (expense != "end" && numExpenses < 20) {
        std::cout << "Expense" << "[" << (numExpenses + 1) << "]: ";
        std::cin >> expense;
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

        std::cout << "Setup Passed ✅\n";
    }
    else {
        std::cout << "Setup Failed ❌\n";
    }

    outputFile.close();

}
