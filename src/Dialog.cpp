#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <cstdlib>
#include <algorithm>

#include "../lib/Dialog.hpp"
#include "../lib/Calculator.hpp"

Dialog::Dialog() {

    option = 0;

}

void Dialog::WelcomeBanner() {

    std::cout << " __  __                _" 
              << "\n|  \\/  | ___  _ __ ___| |"
              << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n| |  | | (_) | | |  __/ |"
              << "\n|_|  |_|\\___/|_|  \\___|_|";

}

void Dialog::Menu() {

    std::cout << "\n\nEnter A Choice From The Menu\n";

    std::cout << "\n\t1. Generate a report"
              << "\n\t2. View a report"
              << "\n\t3. Update a report"
              << "\n\t4. Update an expense"
              << "\n\t5. Help"
              << "\n\t6. Quit";

    std::cout << "\n\nChoice: ";
    std::string choice;
    std::cin >> choice;

    if (ValidateChoice(choice)) {
        option = std::stoi(choice);
    }
    else {
        std::cout << errorMessage;
    }

}

bool Dialog::ValidateChoice(std::string c) {

    bool isValid;

    if (std::all_of(c.begin(), c.end(), ::isdigit) == false) {
        errorMessage = "\nERROR: The value you entered is not an integer";
        isValid = false;
    }

    else if (std::stoi(c) < 0 || std::stoi(c) > 6) {
        errorMessage = "\nERROR: The value entered does not fall within range of 1-6";
        isValid = false;
    }

    else {
        isValid = true;
    }

    return isValid;

}

void Dialog::ReportBanner(std::ostream& stream) {

    stream << " \t __  __                _" 
              << "\n\t|  \\/  | ___  _ __ ___| |"
              << "\n\t| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n\t| |  | | (_) | | |  __/ |"
              << "\n\t|_|  |_|\\___/|_|  \\___|_|";
    
}