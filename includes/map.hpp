/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 01:32:28 by lprates           #+#    #+#             */
/*   Updated: 2023/01/20 22:01:10 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <string>
# include <memory>
# include <limits>
# include <cstddef>
# include <sstream>
# include "utils/pairs.hpp"
# include "utils/map_iterator.hpp"
# include "iterator/reverse_iterator.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"


namespace ft {
	
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<const key_type, mapped_type>							value_type;
			typedef Compare															key_compare;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef ft::mapIterator<value_type, ft::mapNode<value_type> >			iterator;
			typedef ft::mapIterator<const value_type, ft::mapNode<value_type> >		const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef ptrdiff_t														difference_type;
			typedef size_t															size_type;

			class value_compare {
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

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: _data(), _key_cmp(comp), _alloc(alloc), _size(0)
			{
				this->_data = _allocator_rebind_node.allocate(sizeof(ft::mapNode<value_type>));
				_allocator_rebind_node.construct(this->_data, value_type());
				
				this->_ghost = _data;
				this->_ghost->height = 0;
				this->_data->parent = NULL;
			}

			template <class Ite>
			map(
				Ite first,
				Ite last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type()
				) : _data(), _key_cmp(comp), _alloc(alloc), _size(0)
			{
				this->_data = _allocator_rebind_node.allocate(sizeof(ft::mapNode<value_type>));
				_allocator_rebind_node.construct(this->_data, value_type());
				
				this->_ghost = _data;
				this->_ghost->height = 0;
				this->_data->parent = NULL;
				this->_create_data_it(first, last);
			}

			map(const map &src) : _data(), _key_cmp(key_compare()), _alloc(allocator_type()), _size(0)
			{
				this->_data = _allocator_rebind_node.allocate(sizeof(ft::mapNode<value_type>));
				_allocator_rebind_node.construct(this->_data, value_type());
				
				this->_ghost = _data;
				this->_ghost->height = 0;
				this->_data->parent = NULL;
				this->_create_data_it(src.begin(), src.end());
			}

			virtual ~map(void) {
				_tree_clear(this->_data);
				_allocator_rebind_node.destroy(_ghost);
				_allocator_rebind_node.deallocate(_ghost, sizeof(ft::mapNode<value_type>));
			}

			map	&operator=(map const &rhs) {
				if (this == &rhs)
					return (*this);
					
				this->clear();
				this->_data = _allocator_rebind_node.allocate(sizeof(ft::mapNode<value_type>));
				_allocator_rebind_node.construct(this->_data, value_type());
				
				this->_ghost = _data;
				this->_ghost->height = 0;
				this->_data->parent = NULL;
				this->_create_data_it(rhs.begin(), rhs.end());
				return (*this);
			}

			allocator_type	get_allocator() const {
				return (_alloc);
			}

			// Element access

			mapped_type& at(const key_type& key) {
				iterator it = this->find(key);
				if (it == this->end())
					throw std::out_of_range("map::at:  key not found");
				return (it->second);
			}
			const mapped_type& at(const key_type& key) const {
				const_iterator it = this->find(key);
				if (this->end() == it )
					throw std::out_of_range("map::at:  key not found");
				return (it->second);
			}

			mapped_type	&operator[](const key_type &k) {
				return (this->insert(value_type(k, mapped_type())).first->second);
			}

			// Iterators
			
			iterator	begin(void) {
				return (iterator(farLeft(this->_data, _ghost)));
			}

			const_iterator	begin(void) const {
				return (const_iterator(farLeft(this->_data, _ghost)));
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
				return (_allocator_rebind_node.max_size());
			}

			bool	empty(void) const {
				return (this->_size == 0 ? true : false);
			}

			// Modifiers

			ft::pair<iterator, bool> insert(const value_type &val)
			{
				mapNode<value_type> *current = this->_data;
				mapNode<value_type> *parent = NULL;
				mapNode<value_type> *ghost = farRight(this->_data);

				while (current != NULL && current != ghost)
				{
					parent = current;
					if (_key_cmp(val.first, current->data.first))
						current = current->left;
					else if (_key_cmp(current->data.first, val.first))
						current = current->right;
					else
						return (ft::make_pair(iterator(current), false));
				}

				current = _allocator_rebind_node.allocate(sizeof(ft::mapNode<value_type>));
				_allocator_rebind_node.construct(current, val);
				current->parent = parent;

				if (parent == NULL)
					this->_data = current;
				else if (_key_cmp(val.first, parent->data.first))
					parent->left = current;
				else
					parent->right = current;

				if (current->parent == ghost->parent)
				{
					if (parent == NULL) {
						ghost->parent = current;
						current->right = ghost;
					}
					else if (parent != NULL && parent->right == current) {
						ghost->parent = current;
						current->right = ghost;
					}
				}
				this->_rebalance(current);
				++this->_size;
				return (ft::make_pair(iterator(current), true));
			}

			iterator	insert(iterator position, const value_type &val) {
				static_cast<void>(position);
				return (this->insert(val).first);
			}

			template <class Ite>
			void	insert(Ite first, Ite last) {
				while (first != last) 
					this->insert(*first++);
			}

			void	erase(iterator position) {
				iterator tmp = position;
				tmp++;
				this->erase(position, tmp);
			}

			size_type erase(const key_type &k)
			{
				iterator it = this->find(k);
				if (it == this->end())
					return 0;

				node_ptr	nodeToErase = it._node;
				node_ptr	replacementNode = NULL;
				node_ptr	ghost = this->end()._node;
				node_ptr	parentNode = nodeToErase->parent;
				bool		isLeftChild = (parentNode != NULL && parentNode->left == nodeToErase);

				if (nodeToErase->left == NULL || nodeToErase->right == NULL || nodeToErase->right == ghost)
					replacementNode = (nodeToErase->left == NULL) ? nodeToErase->right : nodeToErase->left;
				else
				{
					node_ptr	rightmostNode = nodeToErase->left;
					while (rightmostNode->right != NULL && rightmostNode->right != ghost)
						rightmostNode = rightmostNode->right;

					replacementNode = rightmostNode;
					if (rightmostNode->left && rightmostNode->parent != nodeToErase) {
						rightmostNode->parent->right = rightmostNode->left;
						rightmostNode->left->parent = rightmostNode->parent;
					}
					
					if (nodeToErase->left != replacementNode) {
						if (!rightmostNode->left)
							replacementNode->parent->right = NULL;
						replacementNode->left = nodeToErase->left;
						nodeToErase->left->parent = replacementNode;
					}
					replacementNode->right = nodeToErase->right;
					if (nodeToErase->right)
						nodeToErase->right->parent = replacementNode;
				}

				if (replacementNode != NULL)
					replacementNode->parent = parentNode;
				if (parentNode == NULL)
					this->_data = replacementNode;
				else if (isLeftChild)
					parentNode->left = replacementNode;
				else
					parentNode->right = replacementNode;

				if (nodeToErase->right == ghost && replacementNode != ghost) {
					replacementNode->right = ghost;
					ghost->parent = replacementNode;	
				}
				_allocator_rebind_node.destroy(nodeToErase);
				_allocator_rebind_node.deallocate(nodeToErase, sizeof(ft::mapNode<value_type>));
				this->_rebalance(parentNode);
				--this->_size;

				return 1;
			}

			void	erase(iterator first, iterator last) {
				while (first != last) {
					value_type	tmp = first._node->data;
					first++;
					this->erase(tmp.first);
				}
			}

			void	swap(map &x) {
				map	tmp;
				
				tmp._cpy_content(x);
				x._cpy_content(*this);
				this->_cpy_content(tmp);
			}

			void clear(void)
			{
				_tree_clear(this->_data);
				this->_data = _ghost;
				_ghost->parent = NULL;
				this->_size = 0;
			}

			// Observers

			key_compare	key_comp(void) const {
				return (key_compare());
			}

			value_compare	value_comp(void) const {
				return (value_compare(key_compare()));
			}

			// Operators

			iterator	find(const key_type &k) {
				iterator	it = this->begin();
				iterator	ite = this->end();
				
				while (it != ite) {
					if (this->_key_eq(it->first, k))
						break ;
					it++;
				}
				return (it);
			}

			const_iterator	find(const key_type &k) const {
				const_iterator	it = this->begin();
				const_iterator	ite = this->end();
				
				while (it != ite) {
					if (this->_key_eq(it->first, k))
						break ;
					it++;
				}
				return (it);
			}

			size_type count(const key_type &k) const {
				const_iterator	it = this->begin(), ite = this->end();
				size_type		res = 0;

				while (it != ite)
					if (this->_key_eq((it++)->first, k))
						return (++res);
				return (res);
			}

			iterator	lower_bound(const key_type &k) {
				iterator	it = this->begin();
				iterator	ite = this->end();
				
				while (it != ite) {
					if (!this->_key_cmp(it->first, k))
						break ;
					it++;
				}
				return (it);
			}
			
			const_iterator	lower_bound(const key_type &k) const {
				const_iterator	it = this->begin();
				const_iterator	ite = this->end();
				
				while (it != ite) {
					if (!this->_key_cmp(it->first, k))
						break ;
					it++;
				}
				return (it);
			}

			iterator	upper_bound(const key_type &k) {
				iterator	it = this->begin();
				iterator	ite = this->end();
				
				while (it != ite) {
					if (this->_key_cmp(k, it->first))
						break ;
					it++;
				}
				return (it);
			}

			const_iterator	upper_bound(const key_type &k) const {
				const_iterator	it = this->begin();
				const_iterator	ite = this->end();
				
				while (it != ite) {
					if (this->_key_cmp(k, it->first))
						break ;
					it++;
				}
				return (it);
			}

			pair<iterator, iterator>	equal_range(const key_type &k) {
				pair<iterator, iterator>	res;

				res.first = this->lower_bound(k);
				res.second = this->upper_bound(k);
				return (res);
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type &k) const {
				pair<const_iterator, const_iterator>	res;

				res.first = this->lower_bound(k);
				res.second = this->upper_bound(k);
				return (res);
			}

			private:
				typedef ft::mapNode<value_type>														node_type;
				typedef node_type																	*node_ptr;
				typedef typename allocator_type::template rebind<ft::mapNode<value_type> >::other	allocator_rebind_node;

				node_ptr							_data;
				key_compare							_key_cmp;
				allocator_type						_alloc;
				size_type							_size;
				const static size_type 				_max_size;
				node_ptr							_ghost;
				allocator_rebind_node				_allocator_rebind_node;

				template <class Ite>
				void	_create_data_it(Ite first, Ite last) {
					this->insert(first, last);
				}

				void	_cpy_content(map &src) {
					_tree_clear(this->_data);
					this->_data = _ghost;
					node_ptr tmp = this->_data;
					this->_data = src._data;
					this->_key_cmp = src._key_cmp;
					this->_alloc = src._alloc;
					this->_size = src._size;
					this->_ghost = src._ghost;
					src._data = tmp;
					src._size = 0;
					src._ghost = NULL;
					tmp = NULL;
				}

				bool	_key_eq(const key_type &k1, const key_type &k2) const {
					return (!this->_key_cmp(k1, k2) && !this->_key_cmp(k2, k1));
				}

				void _rebalance(mapNode<value_type> *node)
				{
					while (node != NULL)
					{
						int balance = balanceFactor(node);

						if (balance > 1)
						{
							if (balanceFactor(node->left) < 0)
								node = rotateLeftRight(node);
							else
								node = rotateRight(node);
						}
						else if (balance < -1)
						{
							if (balanceFactor(node->right) > 0)
								node = rotateRightLeft(node);
							else
								node = rotateLeft(node);
						}
						
						if (node != _ghost)
							node->height = std::max(height(node->left), height(node->right)) + 1;
						else
							node->height = 0;
						if (node->parent == NULL)
							this->_data = node;
						node = node->parent;
					}
				}

				void	_tree_clear(node_ptr node)
				{
					if (node == NULL || node == _ghost)
						return;

					_tree_clear(node->left);
					_tree_clear(node->right);
					//std::cout << "deleting node with key: " << node->data.first << " value: " << node->data.second << std::endl;
					_allocator_rebind_node.destroy(node);
					_allocator_rebind_node.deallocate(node, sizeof(ft::mapNode<value_type>));
				}
	};

	// Non member overloads

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs == rhs));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator< (const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return !(rhs < lhs);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator> (const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return (rhs < lhs);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs < rhs);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
		x.swap(y);
	}
	
}

#endif