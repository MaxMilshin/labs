CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude

.PHONY: all
all: lab_13 

lab_13: src/main.cpp include/my_array.hpp 
	$(CXX) $(CXXFLAGS) src/main.cpp -o lab_13

.PHONY: clean
clean:
	rm -rf lab_13
