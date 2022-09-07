#include <iostream>
#include <fstream>

#include "../lib/UpdateExpenseList.hpp"

UpdateExpenseList::UpdateExpenseList() {

    expense = "";
    for (int i = 0; i < sizeof(expenses) / sizeof(expenses[0]); i++) {
        expenses[i] = "";
    }

}

void UpdateExpenseList::Update() {

    Prompt();

    int count = 0;
    while (expense != "end") {
        std::cout << "Expense" << "[" << (count + 1) << "]: ";
        std::cin >> expense;
        std::cout << "\n";
        expenses[count] = expense;
        count++;
    }

    expenseListSize = count;
    Write();

    std::cout << "Updated" << " ✅"
              << "\n\n<><><><><><><><><><><><><><>";

}

void UpdateExpenseList::Prompt() {

    std::cout << "\nGenerate Data Files";

    std::cout << "\n\nPlease give a list of up to 20 expenses"
              << "\nInclude each expense on a seperate line"
              << "\nType 'end' to indicate the end of the list\n\n";

}

void UpdateExpenseList::Write() {

    outputFile.open("expenseList.txt");

    for (int i = 0; i < expenseListSize; i++) {
        outputFile << expenses[i] << "\n";
    }

    outputFile.close();

}