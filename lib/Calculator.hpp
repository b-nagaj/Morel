#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "Dialog.hpp"
#include "ExpenseListUpdater.hpp"
#include "DataFileGenerator.hpp"
#include "TransactionAdder.hpp"
#include "TransactionDeleter.hpp"
#include "ReportGenerator.hpp"
#include "ReportViewer.hpp"

class Calculator {

    public:

        Dialog * myDialog;
        ExpenseListUpdater * myExpenseListUpdater;
        DataFileGenerator * myDataFileGenerator;
        TransactionAdder * myTransactionAdder;
        TransactionDeleter * myTransactionDeleter;
        ReportGenerator * myReportGenerator;
        ReportViewer * myReportViewer;

        //Dialog myDialog;
        // ExpenseListUpdater myExpenseListUpdater;
        // DataFileGenerator myDataFileGenerator;
        // TransactionAdder myTransactionAdder;
        // TransactionDeleter myTransactionDeleter;
        // ReportGenerator myReportGenerator;
        // ReportViewer myReportViewer;

    public:

        Calculator();
        void Prompt();
        ~Calculator();

};

#endif