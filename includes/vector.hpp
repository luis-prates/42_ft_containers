/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 02:12:07 by lprates           #+#    #+#             */
/*   Updated: 2022/11/27 16:46:12 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <sstream>

#ifndef VECTOR_HPP
# define VECTOR_HPP

template< class T, class Allocator = std::allocator<T> >
class vector
{
	public:

		typedef T								value_type;
		typedef Allocator						allocator_type;
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef value_type						&reference;
		typedef const value_type				&const_reference;
		typedef typename allocator_type::pointer		pointer;
		typedef Allocator::const_pointer		const_pointer;
		typedef std::reverse_iterator<iterator> reverse_iterator;

		//TODO: Default constructor. Constructs an empty container with a default-constructed allocator.
		vector();
		//TODO: Constructs an empty container with the given allocator alloc.
		explicit vector( const Allocator& alloc );
		//TODO: Constructs the container with count copies of elements with value value
		explicit vector(
						size_type count,
						const T& value = T(),
						const Allocator& alloc = Allocator()
						);
		//TODO: Constructs the container with the contents of the range [first, last).
		// This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a) if InputIt is an integral type.
		template< class InputIt >
		vector(
				InputIt first,
				InputIt last,
				const Allocator& alloc = Allocator()
				);
		//TODO: Copy constructor. Constructs the container with the copy of the contents of other.
		vector( const vector& other );
};

#endif