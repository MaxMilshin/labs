#pragma once

#include <fstream>
#include <map>
#include <string>

class HuffmanArchiver {
public:
	HuffmanArchiver() = default;
	~HuffmanArchiver() = default;

	void run(std::ifstream &, std::ofstream &);

private:
	void reading(std::ifstream &);
	void writing(std::ifstream &, std::ofstream &);
	void write_code(std::ofstream &, std::string &);

private:
	std::map<char, int> frequency;
	std::map<char, std::string> code;

	size_t input_file_size = 0;
	size_t compress_file_size = 0;
	size_t header_size = 0;
};

class HuffmanDearchiver {
public:
	HuffmanDearchiver() = default;
	~HuffmanDearchiver() = default;

	void run(std::ifstream &, std::ofstream &);

private:
	void read_header(std::ifstream &);
	void writing(std::ifstream &, std::ofstream &);
	void read_file(std::ifstream &, std::ofstream &);
	bool write_byte(std::ofstream &, uint8_t byte, int size);

private:
	std::map<char, int> frequency;
	std::map<std::string, char> code;

	size_t input_file_size = 0;
	size_t output_file_size = 0;
	size_t header_size = 0;
};

class HuffmanTree {
public:
	static void build_code(std::map<char, int> &, std::map<char, std::string> &);
};

