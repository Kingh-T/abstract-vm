/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 19:21:27 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/14 19:33:54 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_T
# define MUTANTSTACK_T

# include <deque>
# include <stack>

//****************************
// CLASS TEMPLATE DECLARATION
//****************************

// template <class T> class MutantStack : public std::stack< T, std::deque<T> > {
template <class T> class MutantStack : public std::stack<T> {
public:
	typedef typename std::deque<T>::iterator iterator;
	MutantStack( void );
	MutantStack( MutantStack const & obj );
	~MutantStack( void );
	MutantStack & operator=( MutantStack const & rhs );

	MutantStack<T>::iterator begin( void );
	MutantStack<T>::iterator end( void );
protected:

private:

};

//****************************
// CLASS TEMPLATE DEFINITION
//****************************

template <class T> MutantStack<T>::MutantStack( void ) {}
template <class T> MutantStack<T>::MutantStack( MutantStack<T> const & obj ) { *this = obj; }
template <class T> MutantStack<T>::~MutantStack( void ) {}
template <class T> MutantStack<T> & MutantStack<T>::operator=( MutantStack<T> const & rhs ) {
	this->std::stack<T>::operator=(rhs);
	return *this;
}
template <class T> typename MutantStack<T>::iterator MutantStack<T>::begin( void ) {
	return this->c.begin();
}
template <class T> typename MutantStack<T>::iterator MutantStack<T>::end( void ) {
	return this->c.end();
}

#endif
