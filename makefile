CXX = g++

all: app

app: app.o Calculator.o
	g++ -g -o app app.o Calculator.o

app.o: app.cpp
	g++ -g -c app.cpp

Calculator.o: Calculator.cpp
	g++ -g -c Calculator.cpp

clean:
	rm -f *.o app