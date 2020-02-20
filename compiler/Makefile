
all: prepare bundle.o parserBase.o sourcerParser.o statementParser.o
	g++ -o release/cx release/obj/*.o


prepare:
	mkdir -p release
	mkdir -p release/obj	
	rm -f release/obj/*.*
	rm -f release/cx

bundle.o: 
	gcc -c cx/lang/bundle.c -o release/obj/bundle.o

parserBase.o:
	gcc -c cx/lang/parserBase.c -o release/obj/parserBase.o

sourcerParser.o:
	gcc -c cx/lang/sourceParser.c -o release/obj/sourceParser.o

statementParser.o:
	gcc -c cx/lang/statementParser.c -o release/obj/statementParser.o




