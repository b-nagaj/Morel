#ifndef REPORT_VIEWER
#define REPORT_VIEWER

#include "utils/Helper.hpp"

class ReportViewer : public Helper {

    public: 

        std::string reportData [29];
        int numReportDataLines;
        const int MAX_REPORT_DATA_LINES = 29;

    public:

        ReportViewer();
        void View();
        void ReadReport();
        void DisplayReport();

};

#endif