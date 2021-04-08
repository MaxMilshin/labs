CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude

.PHONY: all
all: lab_12 

lab_12: obj/main.o obj/matrix.o 
	$(CXX) obj/main.o obj/matrix.o -o lab_12

obj:
	mkdir obj

obj/main.o: src/main.cpp include/matrix.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/matrix.o: src/matrix.cpp include/matrix.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/matrix.cpp -o obj/matrix.o

.PHONY: clean
clean:
	rm -rf lab_12 obj
