.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++98 -Wall -pedantic

all: lab_07

bin:
	mkdir -p bin

lab_07: src/main.cpp bin/matrix.o include/*.hpp bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/%.o: src/%.cpp include/*.hpp bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf bin lab_07