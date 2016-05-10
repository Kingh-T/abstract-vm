/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 23:33:34 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/10 12:44:43 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

//****************************
// CLASS TEMPLATE DEFINITION
//****************************

template<class T> Operand<T>::Operand( void ) { this->_value = std::to_string(static_cast<T>(0)); }
template<class T> Operand<T>::Operand( Operand<T> const & obj ) { *this = obj; }
template<class T> Operand<T>::~Operand( void ) {}
template<class T> Operand<T> & Operand<T>::operator=( Operand<T> const & rhs ) { this->_value = rhs._value; return *this; }

template<class T> Operand<T>::Operand( T value ) { this->_value = std::to_string(value); }
template<class T> Operand<T>::Operand( std::string str ) { this->_value = std::to_string(static_cast<T>(stod(str))); }

template<class T> IOperand const * Operand<T>::operator+( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision()) return (rhs + *this);
	T rhs_value = static_cast<T>(stod(rhs.toString()));
	OperandFactory * factory = new OperandFactory();
	IOperand const * ret_val = factory->createOperand(this->getType(), std::to_string(static_cast<T>(stod(this->_value)) + rhs_value));
	delete factory;
	return ret_val;
}
template<class T> IOperand const * Operand<T>::operator-( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision()) return (rhs + *this);
	T rhs_value = static_cast<T>(stod(rhs.toString()));
	OperandFactory * factory = new OperandFactory();
	IOperand const * ret_val = factory->createOperand(this->getType(), std::to_string(static_cast<T>(stod(this->_value)) - rhs_value));
	delete factory;
	return ret_val;
}
template<class T> IOperand const * Operand<T>::operator*( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision()) return (rhs + *this);
	T rhs_value = static_cast<T>(stod(rhs.toString()));
	OperandFactory * factory = new OperandFactory();
	IOperand const * ret_val = factory->createOperand(this->getType(), std::to_string(static_cast<T>(stod(this->_value)) * rhs_value));
	delete factory;
	return ret_val;
}
template<class T> IOperand const * Operand<T>::operator/( IOperand const & rhs ) const {
	double this_value = stod(this->toString());
	double rhs_value  = stod(rhs.toString());
	if (rhs_value == 0) throw AbstractVM::DivideByZero();
	eOperandType final_type = (this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType());
	OperandFactory * factory = new OperandFactory();
	IOperand const * ret_val = factory->createOperand(final_type, std::to_string(this_value / rhs_value));
	delete factory;
	return ret_val;
}
template<class T> IOperand const * Operand<T>::operator%( IOperand const & rhs ) const {
	long this_value = stol(this->toString());
	long rhs_value  = stol(rhs.toString());
	if (rhs_value == 0) throw AbstractVM::DivideByZero();
	eOperandType final_type = (this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType());
	OperandFactory * factory = new OperandFactory();
	IOperand const * ret_val = factory->createOperand(final_type, std::to_string(this_value % rhs_value));
	delete factory;
	return ret_val;
}

template<class T> std::string const & Operand<T>::toString( void ) const {
	return this->_value;
}

//****************************
// CLASS TEMPLATE SPECIALIZATION
//****************************

template<> int			Operand<int8_t>::getPrecision( void ) const		{ return Int8; }
template<> eOperandType	Operand<int8_t>::getType( void ) const			{ return Int8; }

template<> int			Operand<int16_t>::getPrecision( void ) const	{ return Int16; }
template<> eOperandType	Operand<int16_t>::getType( void ) const			{ return Int16; }

template<> int			Operand<int32_t>::getPrecision( void ) const	{ return Int32; }
template<> eOperandType	Operand<int32_t>::getType( void ) const			{ return Int32; }

template<> int			Operand<float>::getPrecision( void ) const		{ return Float; }
template<> eOperandType	Operand<float>::getType( void ) const			{ return Float; }

template<> int			Operand<double>::getPrecision( void ) const		{ return Double; }
template<> eOperandType	Operand<double>::getType( void ) const			{ return Double; }

//****************************
// CLASS TEMPLATE HARD DECLARATION
//****************************

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
