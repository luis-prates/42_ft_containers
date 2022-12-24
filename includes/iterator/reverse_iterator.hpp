/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:52:26 by lprates           #+#    #+#             */
/*   Updated: 2022/12/24 18:59:26 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "iterator_traits.hpp"


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

			reverse_iterator(): _it() {}
			
			explicit reverse_iterator(iterator_type it): _it(it) {}

			template <typename It>
			reverse_iterator(const reverse_iterator<It>& it): _it(it.base()) {}
			
			iterator_type base() const {
				return (_it);
			}

			reference operator*() const {
			iterator_type tmp = _it;
				return (*--tmp);
			}

			reverse_iterator operator+ (difference_type n) const {
				return (reverse_iterator(this->base() - n));
			}

			friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs)
			{ return rhs.operator+(n); };

			reverse_iterator& operator++() {
				--_it;
				return (*this);
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				--_it;
				return (tmp);
			}

			reverse_iterator &operator+= (difference_type n) {
				_it -= n;
				return (*this);
			}

			reverse_iterator &operator-= (difference_type n) {
				_it += n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const {
				return (reverse_iterator(_it + n));
			}

			/*difference_type operator- (const reverse_iterator& rhs) const {
				return (rhs.base() - this->base());
			}*/

			reverse_iterator& operator--() {
				++_it;
				return (*this);
			}

			reverse_iterator operator-- (int) {
				reverse_iterator tmp = *this;
				++_it;
				return (tmp);
			}

			pointer operator->() const {
				return (&(operator*()));
			}

			reference operator[] (difference_type n) const {
				return (base()[-n-1]);
			}

			bool operator==(const reverse_iterator &rhs) {
				return ((this->base() == rhs.base()));
			}

			bool operator!=(reverse_iterator &rhs) {
				return (base() != rhs.base());
			}

		private:
			iterator_type _it;
	};

	template <typename Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	bool operator==(reverse_iterator<Iterator>& lhs, reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}
	
	template <typename Iterator1, typename Iterator2>
	bool operator==(reverse_iterator<Iterator1>& lhs, reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	bool operator!=(reverse_iterator<Iterator>& lhs, reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!=(reverse_iterator<Iterator1>& lhs, reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) {
		return (reverse_iterator<Iterator>(it.base() - n));
	}

	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() - lhs.base());
	}

} // namespace ft


#endif // REVERSE_ITERATOR_HPP