
all: main.o INTERPRETATOR.o EXECUTOR.o PARSER.o SCANNER.o GLOBAL.o IDENT.o LEX.o
		g++ main.o LEX.o IDENT.o GLOBAL.o SCANNER.o PARSER.o EXECUTOR.o INTERPRETATOR.o

main.o: main.cpp
		g++ main.cpp -c 
		
INTERPRETATOR.o: INTERPRETATOR.cpp INTERPRETATOR.hpp
		g++ INTERPRETATOR.cpp -c 
		
EXECUTOR.o: EXECUTOR.cpp EXECUTOR.hpp
		g++ EXECUTOR.cpp -c 
		
PARSER.o: PARSER.cpp PARSER.hpp
		g++ PARSER.cpp -c 

SCANNER.o: SCANNER.cpp SCANNER.hpp
		g++ SCANNER.cpp -c 
		
GLOBAL.o: GLOBAL.cpp GLOBAL.hpp
		g++ GLOBAL.cpp -c 
		
IDENT.o: IDENT.cpp IDENT.hpp
		g++ IDENT.cpp -c 	 	

LEX.o:  LEX.cpp LEX.hpp
		g++ LEX.cpp -c 

clean:
		rm -f *.o 
		rm -f *.out

