/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IterStack.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 19:21:27 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/09 22:54:05 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERSTACK_T
# define ITERSTACK_T

# include <deque>
# include <stack>

//****************************
// CLASS TEMPLATE DECLARATION
//****************************

// template <class T> class MutantStack : public std::stack< T, std::deque<T> > {
template <class T> class IterStack : public std::stack<T> {
public:
	typedef typename std::deque<T>::iterator iterator;
	IterStack( void );
	IterStack( IterStack const & obj );
	~IterStack( void );
	IterStack & operator=( IterStack const & rhs );

	IterStack<T>::iterator begin( void );
	IterStack<T>::iterator end( void );
protected:

private:

};

//****************************
// CLASS TEMPLATE DEFINITION
//****************************

template <class T> IterStack<T>::IterStack( void ) {}
template <class T> IterStack<T>::IterStack( IterStack<T> const & obj ) { *this = obj; }
template <class T> IterStack<T>::~IterStack( void ) {}
template <class T> IterStack<T> & IterStack<T>::operator=( IterStack<T> const & rhs ) {
	this->std::stack<T>::operator=(rhs);
	return *this;
}
template <class T> typename IterStack<T>::iterator IterStack<T>::begin( void ) {
	return this->c.begin();
}
template <class T> typename IterStack<T>::iterator IterStack<T>::end( void ) {
	return this->c.end();
}

#endif
