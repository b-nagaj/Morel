CXX = g++

all: app

app: app.o Calculator.o GenerateReport.o Dialog.o
	g++ -g -o app app.o Calculator.o GenerateReport.o Dialog.o

app.o: app.cpp
	g++ -g -c app.cpp

Calculator.o: Calculator.cpp
	g++ -g -c Calculator.cpp

GenerateReport.o: GenerateReport.cpp
	g++ -g -c GenerateReport.cpp

Dialog.o: Dialog.cpp
	g++ -g -c Dialog.cpp

clean:
	rm -f *.o app