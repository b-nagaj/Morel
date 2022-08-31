BINARY = app
FILE_OBJECTS = app.o Calculator.o GenerateReport.o GenerateDataFile.o Dialog.o
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

Dialog.o: src/Dialog.cpp
	$(GCC) -c src/Dialog.cpp

clean:
	rm -f *.o app