#include "setup/Setup.hpp"
#include "utils/Banner.hpp"
#include "Calculator.hpp"

#include <filesystem>

/**
 * handles setup for new users and starts the calculator
 */ 
int main() {
    Setup setup;
    Banner banner;
    Calculator calculator;

    banner.DisplayWelcomeBanner();
    calculator.Calculate();

    return 0;
}
