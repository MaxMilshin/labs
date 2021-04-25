#include <set>
#include <iostream>
#include "huffman.hpp"

//________________________________________________________________________
//___________________________HuffmanArchiver______________________________
//________________________________________________________________________

void HuffmanArchiver::run(std::ifstream &in, std::ofstream &out) {
	reading(in);
	HuffmanTree::build_code(frequency, code);
	writing(in, out);

	std::cout << input_file_size << std::endl << compress_file_size << std::endl << header_size << std::endl;
}

void HuffmanArchiver::write_code(std::ofstream &out, std::string &code) {
	static std::string buffer = ""; 
	buffer += code;
	if (code.size() == 0) {
		uint8_t byte = 0;
		int size = buffer.size(); 
		for (int j = 0; j < size; j++) {
			if (buffer[size - j - 1] == '1') {
				byte |= (1 << (j + 8 - size));
			}
		}
		out.write(reinterpret_cast<char*>(&byte), sizeof byte);
		compress_file_size += sizeof byte;
		return;
	}
	std::size_t i = 0;
	for (; i < buffer.size() / 8; i++) {
		std::string byte_str = buffer.substr(i * 8, 8);
		uint8_t byte = 0;
		for (int j = 0; j < 8; j++) {
			if (byte_str[7 - j] == '1') {
				byte |= (1 << j);
			}
		}
		out.write(reinterpret_cast<char*>(&byte), sizeof byte);
		compress_file_size += sizeof byte;
	}
	buffer = buffer.substr(i * 8, buffer.size() - i + 1);
	return;
}

void HuffmanArchiver::reading(std::ifstream &in) {
	while (!in.eof()) {
		char ch;
		if (in.read(&ch, sizeof(char))) {
			frequency[ch]++;
		}
	}
}

void HuffmanArchiver::writing(std::ifstream &in, std::ofstream &out) {
	int symbols_count = frequency.size();
	out.write(reinterpret_cast<char*>(&symbols_count), sizeof symbols_count);
	header_size += sizeof symbols_count;
	int size = 0;
	for (auto pair : frequency) {
		size += pair.second;
		out.write(reinterpret_cast<const char*>(&pair.first), sizeof pair.first);
		out.write(reinterpret_cast<char*>(&pair.second), sizeof pair.second);
		header_size += sizeof pair.first + sizeof pair.second;
	}
	input_file_size += size;
	out.write(reinterpret_cast<char*>(&size), sizeof size);
	header_size += sizeof size;
	in.clear();
	in.seekg(0, in.beg);
	while (!in.eof()) {
		char ch;
		if (in.read(&ch, sizeof(char))) {
			write_code(out, code[ch]);
		}
	}
	std::string empty_string = "";
	write_code(out, empty_string);
}


//________________________________________________________________________
//___________________________HuffmanDearchiver______________________________
//________________________________________________________________________



void HuffmanDearchiver::run(std::ifstream &in, std::ofstream &out) {
	read_header(in);
	
	std::map<char, std::string> helper_code;
	HuffmanTree::build_code(frequency, helper_code);
	for (auto pair : helper_code) {
		code[pair.second] = pair.first;
	}

	read_file(in, out);

	std::cout << input_file_size << std::endl << output_file_size << std::endl << header_size << std::endl;
}

void HuffmanDearchiver::read_header(std::ifstream &in) {
	int symbols_count;
	in.read(reinterpret_cast<char*>(&symbols_count), sizeof symbols_count);
	header_size += sizeof symbols_count;
	for (int i = 0; i < symbols_count; i++) {
		char ch;
		in.read(reinterpret_cast<char*>(&ch), sizeof ch);
		int cnt;
		in.read(reinterpret_cast<char*>(&cnt), sizeof cnt);
		header_size += sizeof ch + sizeof cnt;
		frequency[ch] = cnt;
	}
}

void HuffmanDearchiver::read_file(std::ifstream &in, std::ofstream &out) {
	int size;
	in.read(reinterpret_cast<char*>(&size), sizeof size);
	header_size += sizeof size;
	for (int i = 0; i < size; i++) {
		uint8_t byte;
		in.read(reinterpret_cast<char*>(&byte), sizeof byte);
		input_file_size += sizeof byte;
		if (write_byte(out, byte, size)) {
			break;
		}
	}
}

bool HuffmanDearchiver::write_byte(std::ofstream &out, uint8_t byte, int size) {
	static std::string str = "";
	static int processed_symbols = 0;
	for (int i = 7; i >= 0; i--) {
		if (byte & (1 << i)) {
			str += '1';
		}
		else {
			str += '0';
		}
		if (code.find(str) != code.end()) {
			out.write(reinterpret_cast<char*>(&code[str]), sizeof code[str]);
			output_file_size += sizeof code[str];
			str = "";
			if (++processed_symbols == size) {
				return true;
			}
		}
	}
	return false;
}

//_______________________________________________________________________
//____________________________HuffmanTree________________________________
//_______________________________________________________________________



void HuffmanTree::build_code(std::map<char, int> &frequency, std::map<char, std::string> &code) {
	std::set<std::pair<int, std::string>> freq;

	for (auto pair : frequency) {
		std::string str = "";
		str += pair.first;
		freq.insert(make_pair(pair.second, str));
	}
	
	while (freq.size() > 1) {
		std::string new_item_str = "";
		int new_item_freq = 0;
		for (int j = 0; j < 2; j++) {
			auto first = freq.begin();
			std::string cur_str = (*first).second;
			new_item_str += (*first).second;
			new_item_freq += (*first).first;
			for (std::size_t i = 0; i < cur_str.size(); i++) {
				code[cur_str[i]] += j + '0';
			}
			freq.erase(first);
		}
		freq.insert(make_pair(new_item_freq, new_item_str)); 
	}
	for (auto it = code.begin(); it != code.end(); it++) {
		reverse((*it).second.begin(), (*it).second.end());
	}
}