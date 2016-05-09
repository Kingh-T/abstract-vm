/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 19:22:05 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/09 23:01:48 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include "PolishReverseCalculator.hpp"

#define BUF_SIZE 4000

int main(int argc, char **argv) {
	std::ifstream file;
	std::string contents;
	char buf[BUF_SIZE];
	std::size_t pos;

	if (argc < 2) { std::cerr << "No file given" << std::endl; return 1; } // FIXME
	std::string filename(argv[1]);
	if (argc > 2) { std::cerr << "Usage: ./avm [FILE]" << std::endl; return 1; }
	if (filename.size() == 0) { std::cerr << "Empty filename" << std::endl; return 1; }

	file.open(filename, std::ifstream::in);
	if (file.is_open() == false) { std::cerr << "Could not open " << filename << std::endl; return 1; }

	while (file.get(buf, BUF_SIZE, 0)) { contents.append(buf); }
	file.close();

	std::string line;
	PolishReverseCalculator calc;
	while ((pos = contents.find('\n')) != std::string::npos) {
		line = contents.substr(0, pos);
		contents.erase(0, pos+1);
		if (calc.call(line) == false) return 0;
	}
	if (calc.call(contents) != false) {
		std::cerr << "Error: No exit before EOF" << std::endl;
	}
	return 0;
}
