BINARY = app
FILE_OBJECTS = app.o Calculator.o GenerateReport.o GenerateDataFile.o UpdateExpenseList.o Dialog.o Helper.o
BOOST = -lboost_system -lboost_filesystem
GCC = g++ -std=c++17

build: $(FILE_OBJECTS)
	$(GCC) $(FILE_OBJECTS) -o $(BINARY) $(BOOST)

app.o: src/app.cpp Calculator.o GenerateReport.o GenerateDataFile.o Dialog.o 
	$(GCC) -c src/app.cpp

Calculator.o: src/Calculator.cpp
	$(GCC) -c src/Calculator.cpp

GenerateReport.o: src/GenerateReport.cpp
	$(GCC) -c src/GenerateReport.cpp

GenerateDataFile.o: src/GenerateDataFile.cpp
	$(GCC) -c src/GenerateDataFile.cpp

UpdateExpenseList.o: src/UpdateExpenseList.cpp
	$(GCC) -c src/UpdateExpenseList.cpp

Dialog.o: src/Dialog.cpp
	$(GCC) -c src/Dialog.cpp

Helper.o: src/Helper.cpp
	$(GCC) -c src/Helper.cpp

setup: setup.o
	$(GCC) setup.o -o setup $(BOOST)

setup.o: setup.cpp
	$(GCC) -c setup.cpp

clean:
	rm -f *.o setup app