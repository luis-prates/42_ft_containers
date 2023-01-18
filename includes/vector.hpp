/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 02:12:07 by lprates           #+#    #+#             */
/*   Updated: 2023/01/18 16:22:52 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <algorithm>
# include <stdexcept>
# include <iostream>
# include <typeinfo>
# include <sstream>
# include <cstddef>
# include "iterator/iterator.hpp"
# include "iterator/iterator_traits.hpp"
# include "iterator/reverse_iterator.hpp"
# include "utils/lexicographical_compare.hpp"
# include "utils/equal.hpp"
# include "utils/enable_if.hpp"

namespace ft {
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef size_t											size_type;
			typedef ptrdiff_t										difference_type;
			typedef value_type										&reference;
			typedef const value_type								&const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator> 					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

			protected:
				typedef random_access_iterator<value_type> super;

			public:

			difference_type		operator-(const random_access_iterator<value_type> &n) const { return super::operator-(n); };

			explicit vector( const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0), _ptr(pointer()) {};
			
			explicit vector(
							size_type count,
							const value_type& value = value_type(),
							const allocator_type& alloc = allocator_type()
							): _alloc(alloc), _size(count), _capacity(count)
			{
				if (count > max_size())
					throw std::length_error("Argument size cannot be larger than max size!");
				//std::cout << "Constructing vector :)\n";
				_ptr = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_ptr + i, value);
				
			};
			
			// Constructs the container with the contents of the range [first, last).
			// This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a) if InputIt is an integral type.
			template< class InputIt >
			vector(
					InputIt first,
					InputIt last,
					const allocator_type& alloc = allocator_type(),
					typename enable_if<!is_integral<InputIt>::value>::type* = 0
					): _alloc(alloc), _size(ft::itlen(first, last)), _capacity(ft::itlen(first, last)), _ptr(pointer())
			{
				if (_size > 0) {
					_ptr = _alloc.allocate(_size);
					for (size_type i = 0; first != last; i++, first++) {
						_alloc.construct(_ptr + i, *first);
					}
				}
			}
			
			// Copy constructor. Constructs the container with the copy of the contents of other.
			vector(const vector& src): _alloc(allocator_type()), _size(src._size), _capacity(src._size), _ptr(NULL) {
				if (src._size > 0) {
					_ptr = _alloc.allocate(src.size());
					size_type i = 0;
					for (const_iterator it = src.begin(); it != src.end(); i++, it++)
						_alloc.construct(_ptr + i, *it);
				}
			};

			~vector( void ) {
				clear();
				if (_capacity > 0)
					_alloc.deallocate(_ptr, _capacity);
				_capacity = 0;
			};

			

			void clear() {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				_size = 0;
			}

			size_type size() const {
				return (_size);
			}
			
			size_type max_size() const {
				return (_alloc.max_size());
			};

			size_type capacity() const {
				return (_capacity);
			}

			bool empty() const {
				return (_size == 0);
			}

			void reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n > _capacity && _capacity == 0) {
					pointer temp = _alloc.allocate(n);
					_ptr = temp;
					_capacity = n;
				}
				if (n > _capacity) {
					pointer tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(tmp + i, _ptr[i]);
					size_type tmp_size = _size;
					clear();
					_alloc.deallocate(_ptr, _capacity);
					_ptr = tmp;
					_size = tmp_size;
					_capacity = n;
				}
			}

			void resize(size_type n, value_type val = value_type()) {
				if (n > _capacity)
					reserve(n);
				if (n > _size) {
					for (size_type i = _size; i < n; i++)
						push_back(val);
				} else if (n < _size) {
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_ptr + i);
					_size = n;
				}
			}

			iterator begin() {
				return (iterator(_ptr));
			}

			const_iterator begin() const {
				return (const_iterator(_ptr));
			}

			iterator end() {
				return (iterator(_ptr + _size));
			}

			const_iterator end() const {
				return (const_iterator(_ptr + _size));
			}

			reverse_iterator rbegin() {
				return (reverse_iterator(_ptr + _size));
			}

			const_reverse_iterator rbegin() const {
				return (const_reverse_iterator(_ptr + _size));
			}

			reverse_iterator rend() {
				return (reverse_iterator(_ptr));
			}

			const_reverse_iterator rend() const {
				return (const_reverse_iterator(_ptr));
			}

			reference operator[](size_type n) {
				return reference(_ptr[n]);
			};

			const_reference operator[](size_type n) const {
				return const_reference(_ptr[n]);
			};

			vector& operator=(const vector& x) {
				if (this != &x)
					assign(x.begin(), x.end());
				return (*this);
			}
			
			reference at(size_type n) {
				if (n >= _size)
					throw std::out_of_range(_at_exception_msg(n));
				return (reference(_ptr[n]));
			}

			const_reference at(size_type n) const {
				if (n >= _size)
					throw std::out_of_range(_at_exception_msg(n));
				return (reference(_ptr[n]));
			}

			reference front() {
				return (*_ptr);
			}

			const_reference front() const {
				return (*_ptr);
			}

			reference back() {
				return (*(_ptr + _size - 1));
			}

			const_reference back() const {
				return (*(_ptr + _size - 1));
			}

			template <class InputIt>
			void assign(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type * = 0) {
				clear();
				size_type idx = ft::itlen(first, last);
				resize(idx);
				for (size_type i = 0; i < idx; i++, first++)
					_alloc.construct(_ptr + i, *first);
			}

			void assign(size_type n, const value_type& val) {
				clear();
				resize(n, val);
			}
			
			void push_back(const value_type &val) {
				if (!_capacity)
					reserve(1);
				else if (_size >= _capacity)
					reserve(2 * _capacity);
				_alloc.construct(_ptr + _size++, val);
			}

			void pop_back() {
				if (!empty()) {
					_alloc.destroy(_ptr + _size - 1);
					_size--;
				}
			}

			iterator insert(iterator position, const value_type &val) {
				size_type idx = position - begin();
				pointer idx_ptr;
				
				while (_capacity < _size + 1)
					reserve((_capacity == 0 ? 1 : _capacity * 2));
				idx_ptr = _ptr + idx;
				std::copy(idx_ptr, end().base(), idx_ptr + 1);
				_alloc.construct(idx_ptr, val);
				_size++;
				return (idx_ptr);
			}

			void insert(iterator position, size_type n, const value_type &val) {
				size_type idx = position - begin();
				pointer idx_ptr;
				
				if (_capacity < _size + n)
					reserve(_size + n);
				idx_ptr = _ptr + idx;
				std::copy(idx_ptr, end().base(), idx_ptr + n);
				idx_ptr = _ptr + idx;
				while (n--)
				{
					_alloc.construct(idx_ptr + n, val);
					_size++;
				}
			}

			template <class InputIt>
			void insert(iterator position, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type * = 0) {
				size_type n = ft::itlen(first, last);
				size_type idx = position - begin();
				pointer idx_ptr;
				
				while (_capacity < _size + n)
					reserve((_capacity == 0 ? 1 : _capacity * 2));
				idx_ptr = _ptr + idx;
				std::copy(idx_ptr, end().base(), idx_ptr + n);
				for (size_type i = 0; first != last ; first++, i++, _size++)
					_alloc.construct(idx_ptr + i, *first);
			}

			iterator erase(iterator position) {
				size_type idx = position - begin();
				pointer idx_ptr = _ptr + idx;
				pointer offset_ptr = idx_ptr + 1;
				
				for (; offset_ptr != end().base(); (void)++idx_ptr, (void)++offset_ptr) {
					*idx_ptr = *offset_ptr;
				}
				pop_back();
				return (position);
			}

			iterator erase(iterator first, iterator last) {
				size_type idx = first - begin();
				size_type n = last - first;
				pointer idx_ptr = _ptr + idx;
				pointer offset_ptr = idx_ptr + n;
				
				for (; offset_ptr != end().base(); (void)++idx_ptr, (void)++offset_ptr) {
					*idx_ptr = *offset_ptr;
				}
				while (n-- > 0)
					pop_back();
				return (first);
			}

			void swap(vector& x) {
				std::swap(_ptr, x._ptr);
				std::swap(_capacity, x._capacity);
				std::swap(_size, x._size);
			}

			allocator_type get_allocator() const {
				return (_alloc);
			}

			pointer data() {
				return (pointer(_ptr));
			}

			const_pointer data() const {
				return (const_pointer(_ptr));
			}
			
		private:
			allocator_type		_alloc;
			size_type			_size;
			size_type			_capacity;
			pointer				_ptr;

			const std::string _at_exception_msg(size_type n) const {
				std::stringstream ss;
				ss << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << _size << ")";
				return (ss.str());
			}
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T,Alloc> &x, vector<T,Alloc> &y) {
		x.swap(y);
	}

}

#endif