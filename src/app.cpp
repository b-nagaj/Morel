#include "setup/Setup.hpp"
#include "utils/Dialog.hpp"
#include "Calculator.hpp"

#include <filesystem>

/**
 * handles setup for new users and starts the calculator
 */ 
int main() {
    Setup setup;
    Dialog dialog;
    Calculator calculator;

    dialog.WelcomeBanner();
    calculator.Calculate();

    return 0;
}
