.PHONY: all
all: lab_02

lab_02: obj/str.o obj/test_str.o obj/test.o 
	gcc obj/str.o obj/test_str.o obj/test.o -o lab_02

obj:
	mkdir obj

obj/str.o: src/str.c | obj
	gcc -c -I include src/str.c -o obj/str.o 

obj/test_str.o: src/test_str.c include/str.h | obj
	gcc -c -I include src/test_str.c -o obj/test_str.o

obj/test.o: src/test.c include/test_str.h | obj
	gcc -c -I include src/test.c -o obj/test.o

.PHONY: clean
clean:
	rm -rf lab_02 obj
