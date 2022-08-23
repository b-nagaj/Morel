#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>

#include "Dialog.hpp"

Dialog::Dialog() {

    option = "";

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