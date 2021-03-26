CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++11 -Iinclude

.PHONY: all
all: lab_10 

lab_10: obj/main.o obj/employees.o 
	$(CXX) obj/main.o obj/employees.o -o lab_10

obj:
	mkdir obj

obj/main.o: src/main.cpp include/employees.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/employees.o: src/employees.cpp include/employees.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/employees.cpp -o obj/employees.o

.PHONY: clean
clean:
	rm -rf lab_10 obj
