/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 18:35:43 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/09 19:49:14 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"

char const * AbstractVM::DivideByZero::what( void ) const _NOEXCEPT { return "Cannot divide by zero"; }
char const * AbstractVM::PopOnEmpty::what( void )   const _NOEXCEPT { return "Cannot pop empty stack"; }
char const * AbstractVM::InvalidValue::what( void ) const _NOEXCEPT { return "Instructions contain invalid value"; }
char const * AbstractVM::PrintNotInt8::what( void ) const _NOEXCEPT { return "Cannot print; top value not 8-bit integer"; }
char const * AbstractVM::UnknownInstruction::what( void ) const _NOEXCEPT { return "Unknown instruction"; }
