.PHONY: all
all: lab_06

lab_06: obj/main.o obj/my_vector.o 
	g++ obj/main.o obj/my_vector.o -o lab_06

obj:
	mkdir obj

obj/main.o: src/main.cpp include/my_vector.hpp | obj
	g++ -std=c++17 -c -I include src/main.cpp -o obj/main.o

obj/my_vector.o: src/my_vector.cpp include/my_vector.hpp | obj
	g++ -std=c++17 -c -I include src/my_vector.cpp -o obj/my_vector.o

.PHONY: clean
clean:
	rm -rf lab_06 obj