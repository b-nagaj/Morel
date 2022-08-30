CXX = g++

all: app

app: app.o Calculator.o GenerateReport.o GenerateDataFile.o Dialog.o
	g++ -g -o app app.o Calculator.o GenerateReport.o GenerateDataFile.o Dialog.o

app.o: src/app.cpp
	g++ -g -c src/app.cpp

Calculator.o: src/Calculator.cpp
	g++ -g -c src/Calculator.cpp

GenerateReport.o: src/GenerateReport.cpp
	g++ -g -c src/GenerateReport.cpp

GenerateDataFile.o: src/GenerateDataFile.cpp
	g++ -g -c src/GenerateDataFile.cpp

Dialog.o: src/Dialog.cpp
	g++ -g -c src/Dialog.cpp

clean:
	rm -f *.o app