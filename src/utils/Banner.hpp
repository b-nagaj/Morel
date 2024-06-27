#ifndef BANNER_HPP
#define BANNER_HPP

#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

#include "Helper.hpp"

class Banner : public Helper{
    public:
        void DisplayWelcomeBanner();
        void DisplayReportBanner(std::ostream& stream);
};

#endif
