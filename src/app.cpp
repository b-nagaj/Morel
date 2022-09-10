#include "../lib/Setup.hpp"
#include "../lib/Calculator.hpp"

#include <filesystem>

int main() {


    if (!std::filesystem::exists("config.txt")) {
        Setup s;
        s.BeginSetup();
        main();
    }
    else {
        Calculator c;
        c.Prompt();
    }

    return 0;

}