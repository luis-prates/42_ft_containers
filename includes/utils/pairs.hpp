/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairs.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:19:53 by lprates           #+#    #+#             */
/*   Updated: 2023/01/06 20:26:39 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIRS_HPP
#define PAIRS_HPP

namespace ft {
	template <class T1, class T2>
	struct pair {
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			pair(): first(first_type()), second(second_type()) {}
			
			pair(const first_type &x, const second_type &y): first(x), second(y) {}

			template <class U, class V>
			pair(const pair<U, V> &p): first(p.first), second(p.second) {}

			pair& operator=(const pair &other) {
				if (this != &other)
				{
					first = other.first;
					second = other.second;
				}
				return (*this);
			}
			
			first_type	first;
			second_type	second;
	};

	// https://en.cppreference.com/w/cpp/utility/pair/operator_cmp
	
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		//return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
		return (lhs.first < rhs.first ? true : (rhs.first < lhs.first ? false : (lhs.second < rhs.second ? true : false)));
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y) {
		return (pair<T1, T2>(x, y));
	}
}

#endif