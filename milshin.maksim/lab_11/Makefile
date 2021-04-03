CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude

.PHONY: all
all: lab_11 

lab_11: src/main.cpp include/*.hpp 
	$(CXX) $(CXXFLAGS) src/main.cpp -o lab_11

.PHONY: clean
clean:
	rm -rf lab_11
