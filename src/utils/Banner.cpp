#include "Banner.hpp"

/**
 * Displays a welcome message to the user as well as the app logo
 */ 
void Banner::DisplayWelcomeBanner() {
    GetUsername();
    std::cout << "\nHello, " << username << "!" << std::endl;
    std::cout << " __  __                _" 
              << "\n|  \\/  | ___  _ __ ___| |"
              << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n| |  | | (_) | | |  __/ |"
              << "\n|_|  |_|\\___/|_|  \\___|_|";
}

/**
 * Displays the app logo on a generated report
 * 
 * @param stream an ostream object used to write to the report file
 */ 
void Banner::DisplayReportBanner(std::ostream& stream) {
    stream << " \t __  __                _" 
              << "\n\t|  \\/  | ___  _ __ ___| |"
              << "\n\t| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n\t| |  | | (_) | | |  __/ |"
              << "\n\t|_|  |_|\\___/|_|  \\___|_|";
}
