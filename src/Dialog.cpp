#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>

#include "../lib/Dialog.hpp"
#include "../lib/Calculator.hpp"

Dialog::Dialog() {

    option = "";

}

void Dialog::Banner(std::ostream& stream) {

    stream << " \t __  __                _" 
              << "\n\t|  \\/  | ___  _ __ ___| |"
              << "\n\t| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n\t| |  | | (_) | | |  __/ |"
              << "\n\t|_|  |_|\\___/|_|  \\___|_|";
    
}

int Dialog::Menu() {

    std::cout << "\n\nEnter A Choice From The Menu\n";

    std::cout << "\n\t1. Generate a report"
              << "\n\t2. View a report"
              << "\n\t3. Update a report"
              << "\n\t4. Update an expense"
              << "\n\t5. Help"
              << "\n\t6. Quit";

    std::cout << "\n\nChoice: ";
    std::cin >> option;

    return stoi(option);

}