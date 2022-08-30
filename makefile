CXX = g++

all: app

app: app.o Calculator.o GenerateReport.o GenerateDataFiles.o Dialog.o
	g++ -g -o app app.o Calculator.o GenerateReport.o GenerateDataFiles.o Dialog.o

app.o: src/app.cpp
	g++ -g -c src/app.cpp

Calculator.o: src/Calculator.cpp
	g++ -g -c src/Calculator.cpp

GenerateReport.o: src/GenerateReport.cpp
	g++ -g -c src/GenerateReport.cpp

GenerateDataFiles.o: src/GenerateDataFiles.cpp
	g++ -g -c src/GenerateDataFiles.cpp

Dialog.o: src/Dialog.cpp
	g++ -g -c src/Dialog.cpp

clean:
	rm -f *.o app