#include <iostream>

#include "../lib/Calculator.hpp"

Calculator::Calculator() {
    SetOperation(0);
}

void Calculator::Calculate() {
    while(GetOperation() != NUM_OPERATIONS) {
        DisplayOperations();
        GetOperationFromUser();

        switch(GetOperation()) {
            case 1:
                expenseListUpdater.Update();
                break;
            case 2:
                dataFileGenerator.Generate();
                break;
            case 3:
                transactionAdder.Add();
                break;
            case 4:
                transactionDeleter.Delete();
                break;
            case 5:
                reportGenerator.Generate();
                break;
            case 6:
                reportViewer.View();
                break;
        }
    }
}

int Calculator::GetOperation() {
    return operation;
}

void Calculator::SetOperation(int num) {
    operation = num;
}

void Calculator::DisplayOperations() {
    std::cout << "\n\nEnter the # of an operation from the list\n";

    std::cout << "\n\t1. Update List Of Expenses"
              << "\n\t2. Generate Data Files"
              << "\n\t3. Add a Transaction"
              << "\n\t4. Delete a Transaction"
              << "\n\t5. Generate A Report"
              << "\n\t6. View A Report"
              << "\n\t7. Quit";
}

void Calculator::GetOperationFromUser() {
    std::cout << "\n\nOperation: ";
    std::string uncheckedOperation;
    std::cin >> uncheckedOperation;

    if (ValidateOperation(uncheckedOperation)) {
        std::string checkedOperation = uncheckedOperation;
        SetOperation(std::stoi(checkedOperation));
    }
    else {
        SetOperation(0);
        Calculate();
    }
}

bool Calculator::ValidateOperation(std::string uncheckedOperation) {
    // check if the users input is empty
    if (uncheckedOperation.empty()) {
        std::cout << "\nERROR: Please choose an operation from the list\n\n<><><><><><><><><><><><><><>";
        return false;
    }

    // check if every character in the users input is a digit
    for (char character : uncheckedOperation) {
        if (!std::isdigit(character)) {
            std::cout << "\nERROR: '" << uncheckedOperation << "' is not an integer\n\n<><><><><><><><><><><><><><>";
            return false;
        }
    }

    // check if the users input is within the range of 1-7
    if (std::stoi(uncheckedOperation) < 1 || std::stoi(uncheckedOperation) > 7) {
        std::cout << "\nERROR: '" << uncheckedOperation << "' does not fall within the range of 1 - " << NUM_OPERATIONS << "\n\n<><><><><><><><><><><><><><>";
        return false;
    }
    else {
        return true;
    }
}
