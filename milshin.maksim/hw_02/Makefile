CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++11 -Iinclude

.PHONY: all
all: hw_02 

hw_02: obj/main.o obj/huffman.o 
	$(CXX) obj/main.o obj/huffman.o -o hw_02

obj:
	mkdir obj

obj/main.o: src/main.cpp include/huffman.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/huffman.o: src/huffman.cpp include/huffman.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/huffman.cpp -o obj/huffman.o

.PHONY: clean
clean:
	rm -rf hw_02 obj
