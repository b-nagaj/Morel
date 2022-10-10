#include <iostream>
#include <filesystem>

#include "../lib/ReportViewer.hpp"

ReportViewer::ReportViewer() {

    month = "";
    reportFilesPath = "";
    reportFilename = "";
    numReportDataLines = 0;

    for (int i = 0; i < MAX_REPORT_DATA_LINES; i++) {
        reportData[i] = "";
    }

}

void ReportViewer::View() {

    std::cout << "\nView A Report";

    GetMonth();
    GetPaths();

    std::string prompt = "\nView your " + month + " report? (Y/N): ";
    if (Confirm(prompt)) {
        ReadReport();
        DisplayReport();
    }

    std::cout << "\n\n<><><><><><><><><><><><><><>";

}

void ReportViewer::ReadReport() {

    reportFilename = reportFilesPath + month + "_Report.txt";

    if (std::filesystem::exists(reportFilename)) {
        inputFile.open(reportFilename);

        std::string reportDataLine = "";
        bool endOfReport = false;

        if (inputFile) {
            while (numReportDataLines < MAX_REPORT_DATA_LINES && endOfReport != true) {
                std::getline(inputFile, reportDataLine);
                reportData[numReportDataLines] = reportDataLine;
                numReportDataLines++;

                if (reportDataLine.find("Total") != std::string::npos) {
                    endOfReport = true;
                }
            }
        }

    inputFile.close();
    }
    else {
        std::cout <<  "\nERROR: A report for the month of " + month + " does not exist";
    }

}

void ReportViewer::DisplayReport() {

    for (int i = 0; i < numReportDataLines; i++) {
        std::cout << "\n" << reportData[i];
    }

}