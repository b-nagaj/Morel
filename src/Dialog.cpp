#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include "../lib/Helper.hpp"
#include "../lib/Dialog.hpp"

Dialog::Dialog() {

    username = "";
    option = 0;

}

void Dialog::Menu() {

    std::cout << "\n\nEnter A Choice From The Menu\n";

    std::cout << "\n\t1. Update List Of Expenses"
              << "\n\t2. Generate Data Files"
              << "\n\t3. Generate A Report"
              << "\n\t4. Quit";

    std::cout << "\n\nChoice: ";
    std::string choice;
    std::cin >> choice;

    if (ValidateChoice(choice)) {
        option = std::stoi(choice);
    }

}

void Dialog::WelcomeBanner() {

    GetUsername();
    std::cout << "\nHello, " << username << "!" << std::endl;
    std::cout << " __  __                _" 
              << "\n|  \\/  | ___  _ __ ___| |"
              << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n| |  | | (_) | | |  __/ |"
              << "\n|_|  |_|\\___/|_|  \\___|_|";

}

bool Dialog::ValidateChoice(std::string c) {

    bool isValid;

    if (std::all_of(c.begin(), c.end(), ::isdigit) == false) {
        std::cout << "\nERROR: The value you entered is not an integer\n\n<><><><><><><><><><><><><><>";
        isValid = false;
    }

    else if (std::stoi(c) < 1 || std::stoi(c) > 4) {
        std::cout << "\nERROR: The value entered does not fall within range of 1-7\n\n<><><><><><><><><><><><><><>";
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