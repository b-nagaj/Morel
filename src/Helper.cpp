#include <iostream>

#include "../lib/Helper.hpp"

void Helper::GetUsername() {

    inputFile.open("config.txt"); 
    std::getline(inputFile, username);
    inputFile.close();

}

void Helper::GetPaths() {

    std::string lines [3];

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
        reportFilesPath = lines[2] + "/";
    }
    else {
        reportFilesPath = lines[2];
    }

    inputFile.close();

}

bool Helper::ValidateMonth() {

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

void Helper::GetExpenses() {

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