/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:29:07 by lprates           #+#    #+#             */
/*   Updated: 2022/12/06 23:01:53 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <cstddef>
# include <iterator>
#include "iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class reverse_iterator {
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator(): _it() {};
			explicit reverse_iterator( iterator_type x): _it(x) {};
			template<class U>
			reverse_iterator(const reverse_iterator<U> &other): _it(other.base()) {};
			
			iterator_type base() const {
				return (_it);
			}

			reference operator*() const {
				iterator_type base = _it;
				--tmp;
				return (*tmp);
			}

			reverse_iterator operator+(difference_type n) const {
				return (reverse_iterator(_it - n));
			}

			reverse_iterator& operator++() {
				--_it;
				return (*this);
			}

			reverse_iterator operator++(int) {
				reverse_iterator inc = *this;
				--_it;
				return (inc);
			}
	};
}

#endif