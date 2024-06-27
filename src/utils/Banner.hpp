#ifndef BANNER_HPP
#define BANNER_HPP

#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

#include "Helper.hpp"

class Banner : public Helper {

    public:

        int option;
        const int NUM_MENU_OPTIONS = 7;

    public:
    
        Banner();
        void WelcomeBanner();
        void ReportBanner(std::ostream& stream);

};

#endif
