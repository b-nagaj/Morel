#include "setup/Setup.hpp"
#include "utils/Dialog.hpp"
#include "Calculator.hpp"

#include <filesystem>

int main() {
    Setup setup;
    Dialog dialog;
    Calculator calculator;

    dialog.WelcomeBanner();
    calculator.Calculate();

    return 0;
}
