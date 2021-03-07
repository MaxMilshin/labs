.PHONY: all
all: main

main: obj/main.o obj/all_sorts.o 
	g++ obj/main.o obj/all_sorts.o -o main

obj:
	mkdir obj

obj/main.o: src/main.cpp include/library.hpp | obj
	g++ -std=c++17 -c -I include src/main.cpp -o obj/main.o

obj/all_sorts.o: src/all_sorts.cpp | obj
	g++ -std=c++17 -c -I include src/all_sorts.cpp -o obj/all_sorts.o

.PHONY: clean
clean:
	rm -rf main obj