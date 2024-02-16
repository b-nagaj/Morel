#include "../lib/Setup.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/Calculator.hpp"

#include <filesystem>

int main() {
    Setup setup;
    Dialog dialog;
    Calculator calculator;

    dialog.WelcomeBanner();
    calculator.Calculate();

    return 0;
}