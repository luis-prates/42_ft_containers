/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:41:58 by lprates           #+#    #+#             */
/*   Updated: 2023/01/08 19:25:59 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include <cstddef>
# include "utils/pairs.hpp"

namespace ft {

	template <class T>
	struct mapNode {
		public:
			T			data;
			mapNode		*parent;
			mapNode		*left;
			mapNode		*right;
			int			height;

			mapNode(const T &src = T()) : data(src), parent(NULL), left(NULL), right(NULL), height(1) {};

			mapNode(const mapNode<T> &src)
			{
				this->data = src.data;
				this->parent = src.parent;
				this->left = src.left;
				this->right = src.right;
				this->height = src.height;
			}

			mapNode<T> &operator=(const mapNode<T> &rhs)
			{
				if (this != &rhs)
				{
					this->data = rhs.data;
					this->parent = rhs.parent;
					this->left = rhs.left;
					this->right = rhs.right;
					this->height = rhs.height;
				}

				return *this;
			}

	};

	template <class T>
	mapNode<T> *farRight(mapNode<T> *node) {
		while (node->right != NULL) {
			node->height = std::max(height(node->left), height(node->right)) + 1;
			node = node->right;
		}
		node->height = std::max(height(node->left), height(node->right)) + 1;
		return (node);
	}

	template <class T>
		int height(mapNode<T> *node) {
		if (node == NULL) {
			return 0;
		} else {
			return node->height;
		}
	}

	template <class T>
	int balanceFactor(mapNode<T> *node) {
		return height(node->left) - height(node->right);
	}

	template <class T>
	mapNode<T> *farLeft(mapNode<T> *node) {
		while (node->left != NULL) {
			node->height = std::max(height(node->left), height(node->right)) + 1;
			node = node->left;
		}
		node->height = std::max(height(node->left), height(node->right)) + 1;
		return (node);
	}

	template <class T>
	mapNode<T> *rotateRight(mapNode<T> *node) {
		mapNode<T> *newRoot = node->left;
		node->left = newRoot->right;
		newRoot->right = node;
		node->height = std::max(height(node->left), height(node->right)) + 1;
		newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;
		if (node->parent == NULL) {
			newRoot->parent = NULL;
		}
		else {
			newRoot->parent = node->parent;
			newRoot->parent->left = newRoot;
		}
		node->parent = newRoot;
		return newRoot;
	}

	template <class T>
	mapNode<T> *rotateLeft(mapNode<T> *node) {
		mapNode<T> *newRoot = node->right;
		node->right = newRoot->left;
		newRoot->left = node;
		node->height = std::max(height(node->left), height(node->right)) + 1;
		newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;
		if (node->parent == NULL) {
			newRoot->parent = NULL;
		}
		else {
			newRoot->parent = node->parent;
			newRoot->parent->right = newRoot;
		}
		node->parent = newRoot;
		return newRoot;
	}

	template <class T>
	mapNode<T> *rotateLeftRight(mapNode<T> *node) {
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	template <class T>
	mapNode<T> *rotateRightLeft(mapNode<T> *node) {
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	template <class T, class node_type>
	class mapIterator {
		protected:
			node_type		*_node;
			mapIterator(node_type *src) {
				this->_node = src;
			};
		
		public:
			typedef T											value_type;
			typedef value_type									&reference;
			typedef value_type									*pointer;
			typedef ptrdiff_t									difference_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;

			mapIterator(void) : _node(NULL) {}
			
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

			template <class U>
			bool operator==(const mapIterator<U, node_type> &rhs) const {
				return (this->_node == rhs._node);
			}
			
			template <class U>
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

			template <class, class, class, class>
			friend class map;

			template <class, class>
			friend class mapIterator;
	};
	
} // namespace ft

#endif