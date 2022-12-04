/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 02:12:07 by lprates           #+#    #+#             */
/*   Updated: 2022/12/04 22:55:53 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include "iterator.hpp"

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft {
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef value_type									&reference;
			typedef const value_type							&const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::iterator<value_type>					iterator;
			typedef ft::iterator<const value_type> 				const_iterator;
			typedef std::reverse_iterator<iterator> 			reverse_iterator;
			typedef std::reverse_iterator<const_iterator> 		const_reverse_iterator;

			//TODO: Default constructor. Constructs an empty container with a default-constructed allocator.
			vector();
			//TODO: Constructs an empty container with the given allocator alloc.
			explicit vector( const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0), _ptr(pointer()) {};
			//TODO: Constructs the container with count copies of elements with value value
			explicit vector(
							size_type count,
							const value_type& value = value_type(),
							const allocator_type& alloc = allocator_type()
							): _alloc(alloc), _size(count), _capacity(count)
							{
								if (count > max_size())
									throw std::length_error("Argument size cannot be larger than max size!");
								_ptr = _alloc.allocate(count);
								for (size_type i = 0; i < count; i++)
								{
									_alloc.construct(_ptr + i, value);
								}
								
							};
			//TODO: Constructs the container with the contents of the range [first, last).
			// This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a) if InputIt is an integral type.
			template< class InputIt >
			vector(
					InputIt first,
					InputIt last,
					const allocator_type& alloc = allocator_type()
					);
			//TODO: Copy constructor. Constructs the container with the copy of the contents of other.
			vector( const vector& src );

			~vector( void ) {
				clear();
				if (_capacity > 0)
					_alloc.deallocate(_ptr, _capacity);
				_capacity = 0;
			};

			// Assignment operator
			vector& operator=( const vector& rhs );

			void clear() {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				_size = 0;
			}

			size_type max_size() const {
				return (_alloc.max_size());
			};

			private:
				allocator_type		_alloc;
				size_type			_size;
				size_type			_capacity;
				pointer				_ptr;
	};
}

#endif