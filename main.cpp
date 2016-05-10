/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 19:22:05 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/10 18:05:44 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include "PolishReverseCalculator.hpp"

#define BUF_SIZE 4000
#define MAX_STREAM std::numeric_limits<std::streamsize>::max()

static void	get_line(char* input, int input_size) {
	std::cin.getline(input, input_size);
	if (std::cin.fail()) {
		if (std::cin.gcount() == input_size-1) {						// failed because user entered a word longer than 10 chars
		    std::cout << "* INPUT TOO LONG, CROPPING... *" << std::endl;
		    std::cin.clear();											// clear the fail flags from cin
		    std::cin.ignore(MAX_STREAM, '\n');							// ignore the leftover input from cin
		} else {
			std::cout << "* INPUT ERROR; EXITING *" << std::endl;			// exit if unknown error
			exit(1);
		}
	}
	for (int i=0; input[i]!='\0'; i++) { if (input[i]=='\t') { input[i] = ' '; } }
	return;
}

int main(int argc, char **argv) {
	std::ifstream file;
	std::string contents;
	char buf[BUF_SIZE+1];
	std::size_t pos;
	std::string line;
	PolishReverseCalculator * calc;
	std::string filename;
	bool not_exited;
	bool verbose = false;
	bool cont_on_error = false;
	int first_arg = 1;

	// if (argc < 2) { std::cerr << "Usage: ./avm [--|-v] [FILE]" << std::endl; return 1; }
	if (argc > 1) {
		std::string first = argv[1];
		if (first.size() > 0 && first[0] == '-') {
			first_arg = 2;
			if (first.find('v') != std::string::npos) verbose = true;
			if (first.find('c') != std::string::npos) cont_on_error = true;
		}
	}
	bool read_files = true;
	if (argc == first_arg) {
		first_arg--;
		read_files = false;
		contents = "";
		std::string buf_string;
		while (std::cin.fail() == false) {
			get_line(buf, BUF_SIZE);
			// std::cout << "good:" << std::cin.good() << " eof:" << std::cin.eof() << " fail:" << std::cin.fail() << " bad:" << std::cin.bad() << std::endl;
			// std::cout << "buf:[" << buf << ']' << std::endl;
			contents.append(1, '\n');
			contents.append(buf);
			buf_string = buf;
			if (buf_string.find(";;") != std::string::npos) break;
		}
		// std::cout << "good:" << std::cin.good() << " eof:" << std::cin.eof() << " fail:" << std::cin.fail() << " bad:" << std::cin.bad() << std::endl;
		std::cout << std::endl << "STDIN: " << std::endl;
		std::cout << "v======================v" << std::endl;
	}
	for (int i = first_arg; i < argc; i++) {
		if (read_files) {
			filename = argv[i];
			if (filename.size() == 0) { std::cerr << "Empty filename" << std::endl; return 1; }

			if (i != first_arg) std::cout << "^----------------------^" << std::endl << std::endl;
			std::cout << "File: " << filename << std::endl;
			std::cout << "v======================v" << std::endl;
			file.open(filename, std::ifstream::in);
			if (file.is_open() == false) { std::cerr << "Could not open " << filename << std::endl; continue; }

			contents = "";
			while (file.get(buf, BUF_SIZE, 0)) { contents.append(buf); }
			file.close();
		}

		calc = new PolishReverseCalculator();
		calc->verbose = verbose;
		calc->cont_on_error = cont_on_error;
		not_exited = true;
		while ((pos = contents.find('\n')) != std::string::npos) {
			line = contents.substr(0, pos);
			contents.erase(0, pos+1);
			if (calc->call(line) == false) { not_exited = false; break; }
		}
		if (not_exited && calc->call(contents) != false) {
			std::cerr << "Error: No exit before EOF" << std::endl;
		}
		delete calc;
	}
	return 0;
}
