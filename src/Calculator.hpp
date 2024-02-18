#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "operations/ExpenseListUpdater.hpp"
#include "operations/DataFileGenerator.hpp"
#include "operations/TransactionAdder.hpp"
#include "operations/TransactionDeleter.hpp"
#include "operations/ReportGenerator.hpp"
#include "operations/ReportViewer.hpp"

class Calculator {
    // attributes
    private:
        int operation; // stores the calculator operation selected by the user
        ExpenseListUpdater expenseListUpdater;
        DataFileGenerator dataFileGenerator;
        TransactionAdder transactionAdder;
        TransactionDeleter transactionDeleter;
        ReportGenerator reportGenerator;
        ReportViewer reportViewer;
    public:
        const int NUM_OPERATIONS = 7;
    
    // methods
    private:
        int GetOperation();
        void SetOperation(int num);
        void DisplayOperations(); // display a list of calculator operations available to the user
        void GetOperationFromUser();
        bool ValidateOperation(std::string uncheckedOperation);
    public:
        Calculator();
        void Calculate();
};

#endif
