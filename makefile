CXX=clang++
CXXFLAGS=-std=gnu++14

output: ./src/main.o ./src/game/game.o ./src/printer/printer.o
	g++ -lncurses ./src/main.o ./src/game/game.o ./src/printer/printer.o -o ./bin/tictac.out

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp ./bin/main.o

game.o: ./src/game/game.cpp ./src/game/game.hpp ./src/game/gamestate.hpp
	g++ -c ./src/game/game.cpp ./bin/game.o

printer.o: ./src/printer/printer.cpp ./src/printer/printer.hpp ./src/game/gamestate.hpp
	g++ -c ./src/printer/printer.cpp ./bin/printer.o

clean:
	rm ./src/main.o
	rm ./src/printer/printer.o
	rm ./src/game/game.o
	rm -r ./bin/tictacdebug.out.dSYM
	rm ./bin/tictacdebug.out
	rm ./test/a.out

debug:
	g++ -std=gnu++14 -g -lncurses ./src/main.cpp ./src/game/game.cpp ./src/printer/printer.cpp -o ./bin/tictacdebug.out