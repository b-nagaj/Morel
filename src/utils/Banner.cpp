#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include "Helper.hpp"
#include "Banner.hpp"

Banner::Banner() {

    username = "";
    option = 0;

}

void Banner::WelcomeBanner() {

    GetUsername();
    std::cout << "\nHello, " << username << "!" << std::endl;
    std::cout << " __  __                _" 
              << "\n|  \\/  | ___  _ __ ___| |"
              << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n| |  | | (_) | | |  __/ |"
              << "\n|_|  |_|\\___/|_|  \\___|_|";

}

void Banner::ReportBanner(std::ostream& stream) {

    stream << " \t __  __                _" 
              << "\n\t|  \\/  | ___  _ __ ___| |"
              << "\n\t| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n\t| |  | | (_) | | |  __/ |"
              << "\n\t|_|  |_|\\___/|_|  \\___|_|";
    
}
