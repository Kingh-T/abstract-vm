/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PolishReverseCalculator.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:10:27 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/09 22:59:09 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PolishReverseCalculator.hpp"

PolishReverseCalculator::PolishReverseCalculator( void ) {}

PolishReverseCalculator::PolishReverseCalculator( PolishReverseCalculator const & obj ) { *this = obj; }

PolishReverseCalculator::~PolishReverseCalculator( void ) {
	IterStack<IOperand const*>::iterator i;
	IterStack<IOperand const*>::iterator end = this->stack.end();
	for (i = this->stack.begin(); i != end; i++) { delete &(*i); }
}

PolishReverseCalculator & PolishReverseCalculator::operator=( PolishReverseCalculator const & rhs ) {
	// IterStack<IOperand const*>::iterator i;
	// IterStack<IOperand const*>::iterator end = this->stack.end();
	// for (i = this->stack.begin(); i != end; i++) { delete &(*i); }
	// for (i = rhs.stack.begin(); i != rhs.stack.end(); i++) { this->stack.push(factory.createOperand((*i)->getType(), (*i)->toString())); }
	static_cast<void>(rhs);
	return *this;
}

bool PolishReverseCalculator::call(std::string cmd) {
	try {
		if (cmd == "exit") return false;
		else if (cmd == "pop") { this->pop(); }
		else if (cmd == "dump") { this->dump(); }
		else if (cmd == "print") { this->print(); }
		else if (cmd.substr(0,5) == "push ") { this->push(cmd.substr(5,std::string::npos)); }
		else throw AbstractVM::UnknownInstruction();
		return true;
	} catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return false;
	}
}
void PolishReverseCalculator::push(std::string val) {
	static std::string names[] = {
		std::string("int8"),
		std::string("int16"),
		std::string("int32"),
		std::string("float"),
		std::string("double")
	};
	if (val.size() < 4) throw AbstractVM::InvalidValue();
	if (val.find('(') == std::string::npos) throw AbstractVM::InvalidValue();
	if (val.back() != ')') throw AbstractVM::InvalidValue();
	unsigned int open_p = val.find('(');
	std::string type_string = val.substr(0, open_p);
	std::string value_string = val.substr(open_p+1, val.size()-(open_p+1));
	std::cout << "Pushing " << type_string << ' ' << value_string << std::endl; // DEBUG
	for (int i = Int8; i <= Double; i++ ) {
		if (type_string == names[i]) {
			this->stack.push(factory.createOperand(static_cast<eOperandType>(i), value_string));
			return;
		}
	}
	throw AbstractVM::InvalidValue();
}
void PolishReverseCalculator::pop(void) {
	if (this->stack.size() < 1) throw AbstractVM::PopOnEmpty();
	this->stack.pop();
}
void PolishReverseCalculator::dump(void) {
	IterStack<IOperand const*>::iterator i;
	IterStack<IOperand const*>::iterator end = this->stack.end();
	for (i = this->stack.begin(); i != end; i++) { std::cout << (*i)->toString() << std::endl; }
}

void PolishReverseCalculator::print(void) {
	if (this->stack.size() < 1) throw AbstractVM::PrintNotInt8();
	IOperand const * top = this->stack.top();
	if (top->getType() != Int8) throw AbstractVM::PrintNotInt8();
	char c = std::stoi(top->toString());
	if (c > 32 && c < 127) { std::cout << c << '\n'; }
	else { std::cout << "Non-displayable character (" << std::stoi(top->toString()) << ')' << std::endl; }
}
