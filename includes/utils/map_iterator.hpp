/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:41:58 by lprates           #+#    #+#             */
/*   Updated: 2023/01/03 00:16:41 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "utils/pairs.hpp"

namespace ft {

	template<typename T>
	struct mapNode {
		public:
			T			data;
			mapNode		*parent;
			mapNode		*left;
			mapNode		*right;

			mapNode(const T &src = t()) : data(src), parent(NULL), left(NULL), right(NULL) {};
	};

	template<typename T>
	mapNode<T> *farRight(mapNode<T> *node) {
		while (node->right !=)
			node = node->right;
		return (node);
	}

	template<typename T>
	mapNode<T> *farLeft(mapNode<T> *node) {
		while (node->left !=)
			node = node->left;
		return (node);
	}

	template<class T, class node_type>
	class mapIterator {
		protected:
			node_type		*_node;
			mapIterator(node_type *src);
		
		public:
			typedef T				value_type:
			typedef value_type		&reference;
			typedef value_type		*pointer;
			typedef ptrdiff_t		difference_type;

			mapIterator(void) : _node(NULL) {}
			
			mapIterator(node_type *src) {
				this->node = src;
			}
			
			mapIterator(const mapIterator &src) {
				*this = src;
			}
			
			virtual ~mapIterator(void) {};
			
			mapIterator &operator=(mapIterator const &rhs) {
				if (this == &rhs)
					return (*this);
				this->_node = rhs._node;
				return (*this);
			}

			template<class U>
			bool operator==(const mapIterator<U, node_type> &rhs) const {
				return (this->_node == rhs._node);
			}
			
			template<class U>
			bool operator!=(const mapIterator<U, node_type> &rhs) const {
				return (this->_node != rhs._node);
			}

			mapIterator &operator++(void) {
				if (this->_node->right != NULL)
					this->_node = farLeft(this->_node->right);
				else {
					node_type	*child = this->_node;

					this->_node = this->_node->parent;
					while (this->_node && child == this->_node->right) {
						child = this->_node;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			}
			
			mapIterator operator++(int) {
				mapIterator tmp(*this);
				++(*this);
				return (tmp);
			}
			
			mapIterator &operator--(void) {
				if (this->_node->left != NULL)
					this->_node = farRight(this->_node->left);
				else {
					node_type	*child = this->_node;

					this->_node = this->_node->parent;
					while (this->_node && child == this->_node->left) {
						child = this->_node;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			}
			
			mapIterator operator--(int) {
				mapIterator tmp(*this);
				--(*this);
				return (tmp);
			}

			reference operator*(void) const {
				return (this->_node->data);
			}
			
			pointer operator->(void) const {
				return (&this->operator*());
			};

			operator mapIterator<const T, node_type>(void) const {
				return mapIterator<const T, node_type>(this->_node);
			}
	}
	
} // namespace ft