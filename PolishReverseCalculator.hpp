/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PolishReverseCalculator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:10:27 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/10 16:14:37 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLISHREVERSECALCULATOR_H
# define POLISHREVERSECALCULATOR_H

# include "IterStack.hpp"
# include "OperandFactory.hpp"
# include "AbstractVM.hpp"
# include <string>
# include <iostream>
# include <sstream>
# include <vector>
# include <algorithm>

class PolishReverseCalculator {
public:
	PolishReverseCalculator( void );
	PolishReverseCalculator( PolishReverseCalculator const & obj );

	~PolishReverseCalculator( void );

	PolishReverseCalculator & operator=( PolishReverseCalculator const & rhs );

	bool call(std::string cmd);
	void push(std::string val);
	void pop(void);
	void dump(void);
	void print(void);

	bool verbose;
	bool cont_on_error;
private:
	IterStack<IOperand const*> stack;
	OperandFactory factory;
};

#endif
