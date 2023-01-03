/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 01:32:28 by lprates           #+#    #+#             */
/*   Updated: 2023/01/03 01:43:12 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <map>
# include "utils/pairs.hpp"
# include "utils/map_iterator.hpp"


namespace ft {
	
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef ft::pair<const key_type, mapped_type>				value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			
			typedef ft::mapNode<value_type>								node_type;
			typedef node_type											*node_ptr;
			
			typedef ft::mapIterator<value_type, node_type>				iterator;
			typedef ft::mapIterator<const value_type, node_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;

			class value_compare : std::binary_function<value_type, value_type, bool> {
				private:
					friend class map;

				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {};

				public:
					typedef bool				result_type;
					typedef value_type			first_argument_type;
					typedef value_type			second_argument_type;
					
					bool operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

			explicit map(const key_compare &comp, const allocator_type &alloc = allocator_type())
				: _data(), _key_cmp(comp), _alloc(alloc), _size(0) {
					this->_data = new node_type;
			}

			template<class Ite>
			map(
				Ite first,
				Ite last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type()
				) : _data(), _key_cmp(comp), _alloc(alloc), _size(0) {
					this->_data = new node_type;
					this->_create_data_it(first, last);
			}

			map(const map &src) : _data(), _key_cmp(key_compare()), _alloc(allocator_type()), _size(0) {
				this->_data = new node_type;
				*this = src;
			}

			virtual ~map(void) {
				this->clear();
				delete this->_data;
			}

			map	&operator=(map const &rhs) {
				if (this == &rhs)
					return (*this);
				this->clear();
				this->_create_data_it(rhs.begin(), rhs.end());
				return (*this);
			}

			// Iterators
			
			iterator	begin(void) {
				return (iterator(farLeft(this->_data)));
			}

			const_iterator	begin(void) const {
				return (const_iterator(farLeft(this->_data)));
			}

			iterator	end(void) {
				return (iterator(farRight(this->_data)));
			}

			const_iterator	end(void) const {
				return (const_iterator(farRight(this->_data)));
			}

			reverse_iterator	rbegin(void) {
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator	rbegin(void) const {
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator	rend(void) {
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator	rend(void) const {
				return (const_reverse_iterator(this->begin()));
			}

			// Capacity

			size_type	size(void) const {
				return (this->_size);
			}

			size_type	max_size(void) const {
				return (this->_max_size);
			}

			bool	empty(void) const {
				return (this->_size == 0 ? true : false);
			}

			// Element access

			mapped_type	&operator[](const key_type &k) {
				return (this->insert(value_type(k, mapped_type())).first->second);
			}

			// Modifiers

			ft::pair<iterator, bool>	insert(const value_type &val) {
				ft::pair<iterator, bool> res;

				res.second = !this->count(val.first);
				if (res.second == true)
					this->_btree_add(new node_type(val));
				res.first = this->find(val.first);
				return (res);
			}

			iterator	insert(iterator position, const value_type &val) {
				static_cast<void>(position);
				return (this->insert(val).first);
			}

			template<class Ite>
			void	insert(Ite first, Ite last) {
				while (first != last)
					this->insert(*first++);
			}

			private:
				node_ptr				_data;
				key_compare				_key_cmp;
				allocator_type			_alloc;
				size_type				_size;
				const static size_type 	_max_size;

				template<class Ite>
				void	_create_data_it(Ite first, Ite last) {
					this->insert(first, last);
				}

			
	};
}

#endif