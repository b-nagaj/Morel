#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "operations/AddTransaction.hpp"
#include "operations/DeleteTransaction.hpp"
#include "operations/UpdateTransaction.hpp"

#include <iostream>

class Calculator {
    // attributes
    private:
        int operation; // stores the calculator operation selected by the user
        AddTransaction addTransaction;
        DeleteTransaction deleteTransaction;
        UpdateTransaction updateTransaction;
    public:
        const int NUM_OPERATIONS = 8;
    
    // methods
    private:
        int GetOperation();
        void SetOperation(int num);
        void DisplayOperations(); // display a list of calculator operations
        void GetOperationFromUser();
        bool ValidateOperation(std::string uncheckedOperation);
    public:
        Calculator();
        void Calculate();
};

#endif
