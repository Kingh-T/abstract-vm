/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 18:35:43 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/10 13:28:55 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_H
# define ABSTRACTVM_H

# include <exception>

struct AbstractVM {
	struct DivideByZero : public std::exception { char const * what( void ) const _NOEXCEPT; };
	struct PopOnEmpty   : public std::exception { char const * what( void ) const _NOEXCEPT; };
	struct InvalidValue : public std::exception { char const * what( void ) const _NOEXCEPT; };
	struct PrintNotInt8 : public std::exception { char const * what( void ) const _NOEXCEPT; };
	struct UnknownInstruction : public std::exception { char const * what( void ) const _NOEXCEPT; };
	struct UnknownOperation : public std::exception { char const * what( void ) const _NOEXCEPT; };
	struct NotEnoughValues : public std::exception { char const * what( void ) const _NOEXCEPT; };
	struct AssertNotTrue : public std::exception { char const * what( void ) const _NOEXCEPT; };
};

#endif
