#include "Calculator.hpp"

/**
 * initializes the calculator option to '0'
 */ 
Calculator::Calculator() {
    SetOperation(0);
}

/**
 * runs a loop continously that gets user input and executes the matching operation
 */ 
void Calculator::Calculate() {
    while(GetOperation() != NUM_OPERATIONS) {
        DisplayOperations();
        GetOperationFromUser();

        switch(GetOperation()) {
            case 1:
                addTransaction.Add();
                break;
            case 2:
                deleteTransaction.Delete();
                break;
            case 3:
                std::cout << "\ncoming soon!";
                break;
            case 4:
                std::cout << "\ncoming soon!";
                break;
            case 5:
                std::cout << "\ncoming soon!";
                break;
            case 6:
                std::cout << "\ncoming soon!";
                break;
            case 7:
                std::cout << "\ncoming soon!";
                break;
        }
    }
}

/**
 * Gets the last operation entered by the user
 * 
 * @return operation
 */ 
int Calculator::GetOperation() {
    return operation;
}

/**
 * Sets the operation based on input from the user
 * 
 * @param num user input that represents an operation
 */ 
void Calculator::SetOperation(int num) {
    operation = num;
}

/**
 * displays a menu of calculator operations available to the user
 */ 
void Calculator::DisplayOperations() {
    std::cout << "\n\nEnter the # of an operation from the list\n";

    std::cout << "\n\t1. Add a Transaction"
              << "\n\t2. Delete a Transaction"
              << "\n\t3. Edit a Transaction"
              << "\n\t4. Modify a Transaction"
              << "\n\t5. View Transactions"
              << "\n\t6. Generate a Report"
              << "\n\t7. View a Report"
              << "\n\t8. Quit";
}

/**
 * accepts user input to determine the next operation
 */ 
void Calculator::GetOperationFromUser() {
    std::cout << "\n\nOperation: ";
    std::string uncheckedOperation;
    std::getline(std::cin, uncheckedOperation);

    if (ValidateOperation(uncheckedOperation)) {
        std::string checkedOperation = uncheckedOperation;
        SetOperation(std::stoi(checkedOperation));
    }
    else {
        SetOperation(0);
        Calculate();
    }
}

/**
 * validates that user input for an operation
 * isn't empty and doesn't contain numbers
 */ 
bool Calculator::ValidateOperation(std::string uncheckedOperation) {
    // check if the users input is empty
    if (uncheckedOperation.empty()) {
        std::cout << "\nERROR: Please choose an operation from the list\n\n";
        return false;
    }

    // check if every character in the users input is a digit
    for (char character : uncheckedOperation) {
        if (!std::isdigit(character)) {
            std::cout << "\nERROR: '" 
                      << uncheckedOperation 
                      << "' is not an integer\n\n";
            return false;
        }
    }

    // check if the users input is within the range of 1-7
    if (std::stoi(uncheckedOperation) < 1 || std::stoi(uncheckedOperation) > NUM_OPERATIONS) {
        std::cout << "\nERROR: '" 
                  << uncheckedOperation 
                  << "' does not fall within the range of 1 - " 
                  << NUM_OPERATIONS 
                  << "\n\n";
        return false;
    }
    else {
        return true;
    }
}
