
all: prepare scope.o parserBase.o 
	@echo "Preparing All..."

prepare:
	@mkdir -p release
	@mkdir -p release/obj	
	@rm -f release/obj/*.*
	@rm -f release/cx

scope.o: 
	gcc -c cx/lang/scope.c -o release/obj/scope.o

parserBase.o:
	gcc -c cx/lang/parser/parserBase.c -o release/obj/parserBase.o

sourcerParser.o:
	gcc -c cx/lang/sourceParser.c -o release/obj/sourceParser.o

statementParser.o:
	gcc -c cx/lang/statementParser.c -o release/obj/statementParser.o


simpleClass: prepare parserBase.o scope.o
	gcc -c tests/simpleClass.c -o release/obj/simpleClass.o
	g++ -o release/simpleClass release/obj/*.o
	@echo "\n\n********************************************************************************\n"
	@./release/simpleClass



