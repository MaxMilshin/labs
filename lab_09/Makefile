CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude

OBJECTS = obj/Scheme.o obj/Rectangle.o obj/Circle.o obj/Figure.o 
HEADERS = include/Scheme.hpp include/Rectangle.hpp include/Circle.hpp

.PHONY: all
all: lab_09 test

lab_09: obj/main.o $(OBJECTS) 
	$(CXX) obj/main.o $(OBJECTS) -o lab_09

test: obj/test.o $(OBJECTS)
	$(CXX) obj/test.o $(OBJECTS) -o test

obj:
	mkdir obj

obj/main.o: src/main.cpp $(HEADERS) | obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/test.o: src/test.cpp $(HEADERS) | obj
	$(CXX) $(CXXFLAGS) -c src/test.cpp -o obj/test.o

obj/Scheme.o: src/Scheme.cpp include/Scheme.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/Scheme.cpp -o obj/Scheme.o

obj/Rectangle.o: src/Rectangle.cpp include/Rectangle.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/Rectangle.cpp -o obj/Rectangle.o

obj/Circle.o: src/Circle.cpp include/Circle.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/Circle.cpp -o obj/Circle.o

obj/Figure.o: src/Figure.cpp include/Figure.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/Figure.cpp -o obj/Figure.o

.PHONY: clean
clean:
	rm -rf lab_09 test obj
