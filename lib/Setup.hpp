#ifndef SETUP_HPP
#define SETUP_HPP

#include <string>
#include <fstream>

class Setup {

    public:

        std::string expenses [20];
        std::string expense;
        int numExpenses; 
        std::string username;
        std::string dataFilesPath;
        std::string reportFilesPath;
        std::ofstream outputFile;

        Setup();
        void BeginSetup();
        void Prompt();
        void WelcomeBanner();
        void GetUsername();
        void GetPaths();
        bool ValidatePaths();
        void GetExpenseList();
        void Write();

};

#endif