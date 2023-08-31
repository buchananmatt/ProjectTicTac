CXX=clang++
CXXFLAGS=-std=c++14

output: ./src/main.o ./src/computer/computer.o ./src/console/console.o ./src/game/game.o ./src/printer/printer.o
	g++ ./src/main.o ./src/computer/computer.o ./src/console/console.o ./src/game/game.o ./src/printer/printer.o -o ./bin/tictac.out

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp

computer.o: ./src/computer/computer.cpp ./src/computer/computer.hpp
	g++ -c ./src/computer/computer.cpp

console.o: ./src/console/console.cpp ./src/console/console.hpp
	g++ -c ./src/console/console.cpp

game.o: ./src/game/game.cpp ./src/game/game.hpp
	g++ -c ./src/game/game.cpp

printer.o: ./src/printer/printer.cpp ./src/printer/printer,hpp
	g++ -c ./src/printer/printer.cpp

clean:
	rm ./src/*.o
	rm ./src/computer/*.o
	rm ./src/console/*.o
	rm ./src/game/*.o
	rm ./src/printer/*.o