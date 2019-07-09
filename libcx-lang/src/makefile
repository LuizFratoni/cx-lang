
all: CxClass.o debug.o
	g++ -o debug CxClass.o debug.o
	./debug

CxClass.o: CxClass.c
	gcc -c CxClass.c -o CxClass.o

debug.o: debug.cpp
	g++ -c debug.cpp -o debug.o


