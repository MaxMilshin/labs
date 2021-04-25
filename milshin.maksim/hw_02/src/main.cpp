#include <string.h>
#include <fstream>

#include "huffman.hpp"

int main(int argc, char **argv) {
	if (strcmp(argv[1], "-c") == 0) {
		std::ifstream in(argv[3], std::ios::in);
		std::ofstream out(argv[5], std::ios::out);
		HuffmanArchiver().run(in, out);
	}
	if (strcmp(argv[1], "-u") == 0) {
		std::ifstream in(argv[3], std::ios::in);
		std::ofstream out(argv[5], std::ios::out);
		HuffmanDearchiver().run(in, out);
	}
}