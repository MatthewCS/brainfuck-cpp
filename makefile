CXX = g++
HEADERS = -I./headers

main: bin/main.o
	$(CXX) -o main bin/main.o bin/Brainfuck.o bin/Tape.o $(HEADERS)

bin/main.o: source/main.cpp bin/Brainfuck.o
	$(CXX) -o bin/main.o -c source/main.cpp $(HEADERS)

bin/Brainfuck.o: source/Brainfuck.cpp headers/Brainfuck.h bin/Tape.o
	$(CXX) -o bin/Brainfuck.o -c source/Brainfuck.cpp $(HEADERS)

bin/Tape.o: source/Tape.cpp headers/Tape.h
	$(CXX) -o bin/Tape.o -c source/Tape.cpp $(HEADERS)

clean:
	rm bin/*.o
