/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PolishReverseCalculator.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:10:27 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/10 16:14:51 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PolishReverseCalculator.hpp"

PolishReverseCalculator::PolishReverseCalculator( void ) : verbose(false), cont_on_error(false) {}

PolishReverseCalculator::PolishReverseCalculator( PolishReverseCalculator const & obj ) : verbose(false), cont_on_error(false) { *this = obj; }

PolishReverseCalculator::~PolishReverseCalculator( void ) {
	IterStack<IOperand const*>::iterator i;
	IterStack<IOperand const*>::iterator end = this->stack.end();
	for (i = this->stack.begin(); i != end; i++) { delete *i; }
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
	static const std::vector<std::string> ops = { "add", "sub", "mul", "div", "mod" };
	try {
		if (cmd.find(';') != std::string::npos) cmd.erase(cmd.find(';'), std::string::npos);
		if (cmd.find_first_not_of(" \t") != 0) cmd.erase(0, cmd.find_first_not_of(" \t"));
		while (cmd.size() != 0 && cmd.find_last_of(" \t") == cmd.size()-1) cmd.pop_back();
		if (cmd.size() == 0) return true;
		else if (cmd == "exit") return false;
		else if (cmd == "pop") { this->pop(); }
		else if (cmd == "dump") { this->dump(); }
		else if (cmd == "print") { this->print(); }
		else if (cmd.substr(0,5) == "push ") { this->push(cmd.substr(5,std::string::npos)); }
		else if (std::find(ops.begin(), ops.end(), cmd) != ops.end()) {
			if (this->stack.size() < 2) throw AbstractVM::NotEnoughValues();
			IOperand const * rhs = this->stack.top();
			this->stack.pop();
			IOperand const * lhs = this->stack.top();
			this->stack.pop();
			IOperand const * created = nullptr;
			if (cmd == "add") created = *lhs + *rhs;
			else if (cmd == "sub") created = *lhs - *rhs;
			else if (cmd == "mul") created = *lhs * *rhs;
			else if (cmd == "div") created = *lhs / *rhs;
			else if (cmd == "mod") created = *lhs % *rhs;
			else throw AbstractVM::UnknownOperation();
			this->stack.push(created);
			delete lhs;
			delete rhs;
		}
		else if (cmd.substr(0,7) == "assert ") {
			this->push(cmd.substr(7,std::string::npos));
			IOperand const * lhs = this->stack.top();
			this->stack.pop();
			IOperand const * rhs = this->stack.top();
			if (lhs->getType() != rhs->getType() || lhs->toString() != rhs->toString())
				throw AbstractVM::AssertNotTrue();
			delete lhs;
		}
		else {
			if (this->verbose) std::cout << "Error: Unknown instruction: " << cmd << std::endl;
			else throw AbstractVM::UnknownInstruction();
		}
		return true;
	} catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return this->cont_on_error;
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
	val.pop_back();
	unsigned int open_p = val.find('(');
	std::string type_string = val.substr(0, open_p);
	val.erase(val.begin(), val.begin()+open_p+1);
	if (this->verbose) std::cout << "Pushing " << type_string << ' ' << val << std::endl; // DEBUG
	for (int i = Int8; i <= Double; i++ ) {
		if (type_string == names[i]) {
			this->stack.push(factory.createOperand(static_cast<eOperandType>(i), val));
			return;
		}
	}
	throw AbstractVM::InvalidValue();
}
void PolishReverseCalculator::pop(void) {
	if (this->stack.size() < 1) throw AbstractVM::PopOnEmpty();
	delete this->stack.top();
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
