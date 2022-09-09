#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <boost/filesystem.hpp>

class Setup {

    public: 

        std::string expenses [20];
        std::string expense;
        int numExpenses; 
        std::string username;
        std::string dataFilesPath;
        std::string reportFilesPath;
        std::ofstream outputFile;

        Setup() {

            for (int i = 0; i < 20; i++) {
                expenses[i] = "";
            }

            expense = "";
            numExpenses = 0;
            username = "";
            dataFilesPath = "";
            reportFilesPath = "";

        }

        void Prompt() {

            GetUsername();
            GetPaths();

            if (ValidatePaths()) {
                GetExpenseList();
                Write();
            }
            else {
                Prompt();
            }

        }

        void WelcomeBanner() {

            std::cout << " __  __                _" 
                      << "\n|  \\/  | ___  _ __ ___| |"
                      << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
                      << "\n| |  | | (_) | | |  __/ |"
                      << "\n|_|  |_|\\___/|_|  \\___|_|";

            std::cout << "\n\nSetup";

        }

        void GetUsername() {

            std::cout << "\n\nUsername: ";
            std::cin >> username;

        }

        void GetPaths() {

            std::cout << "\nPath to store data files (include an absolute path): ";
            std::cin >> dataFilesPath;

            std::cout << "\nPath to store report files (include an absolute path): ";
            std::cin >> reportFilesPath;

        }

        bool ValidatePaths() {

            bool validPath = false;

            if (boost::filesystem::exists(dataFilesPath) && boost::filesystem::exists(reportFilesPath)) {
                validPath = true;
            }
            else {
                std::cout << "\nERROR: The path(s) you entered does not exist";
            }

            return validPath;

        }

        void GetExpenseList() {

            std::cout << "\nPlease give a list of up to 20 expenses"
                      << "\nInclude each expense on a seperate line"
                      << "\nType 'end' to indicate the end of the list\n\n";

            while (expense != "end" && numExpenses < 20) {
                std::cout << "Expense" << "[" << (numExpenses + 1) << "]: ";
                std::cin >> expense;
                std::cout << "\n";
                expenses[numExpenses] = expense;
                numExpenses++;
            }
            numExpenses--;

        }

        void Write() {

            outputFile.open("config.txt");

            if(outputFile) {
                outputFile << username << std::endl
                           << dataFilesPath << std::endl
                           << reportFilesPath << std::endl;
                
                for (int i = 0; i < (numExpenses); i++) {
                    outputFile << expenses[i] << std::endl;
                }

                std::cout << "Setup Passed ✅\n\n";
            }
            else {
                std::cout << "Setup Failed ❌\n\n";
            }

            outputFile.close();

        }

};

int main() {

    Setup mySetup;
    mySetup.WelcomeBanner();
    mySetup.Prompt();

}
