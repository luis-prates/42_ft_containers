/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:56:08 by lprates           #+#    #+#             */
/*   Updated: 2023/01/20 21:12:03 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "iterator_traits.hpp"

struct random_access_iterator_tag;

namespace ft {

	template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};
	
	template <class T>
	class random_access_iterator : public ft::iterator< random_access_iterator_tag, T > {
		public:
			typedef typename ft::iterator< ft::random_access_iterator_tag, T >::value_type			value_type;
        	typedef typename ft::iterator< ft::random_access_iterator_tag, T >::difference_type		difference_type;
        	typedef typename ft::iterator< ft::random_access_iterator_tag, T >::pointer				pointer;
        	typedef typename ft::iterator< ft::random_access_iterator_tag, T >::reference			reference;
        	typedef typename ft::iterator< ft::random_access_iterator_tag, T >::iterator_category	iterator_category;

			random_access_iterator() : _ptr(NULL) {}

			random_access_iterator(pointer ptr) : _ptr(ptr) {}
			
			random_access_iterator(const random_access_iterator &ref) : _ptr(ref._ptr) {}

			virtual ~random_access_iterator() {}

			random_access_iterator &operator=(const random_access_iterator &ref) {
				if (this != &ref)
					_ptr = ref._ptr;
				return (*this);
			}

			pointer	base( void ) const {
				return ( this->_ptr );
			}

			operator random_access_iterator<const value_type>() const {
				return random_access_iterator<const value_type>(_ptr);
			}

			random_access_iterator &operator--() {
				this->_ptr--;
				return (*this);
			}

			random_access_iterator operator--(int) {
				random_access_iterator it(*this);
				this->_ptr--;
				return (it);
			}

			random_access_iterator &operator-=(const difference_type &n) {
				this->_ptr -= n;
				return (*this);
			}

			random_access_iterator operator-(const difference_type &n) const {
				return (random_access_iterator(this->_ptr - n));
			}

			difference_type operator-(const random_access_iterator<value_type> &ref) const {
				return ( base() - ref.base());
			}

			random_access_iterator &operator++() {
				this->_ptr++;
				return (*this);
			}

			random_access_iterator operator++(int) {
				random_access_iterator it(*this);
				operator++();
				return (it);
			}

			random_access_iterator &operator+=(const difference_type &n) {
				this->_ptr += n;
				return (*this);
			}

			random_access_iterator operator+(const difference_type &n) const {
				random_access_iterator it(this->_ptr + n);
				return (it);
			}

			// have to check the friend operator+ function
			friend random_access_iterator operator+(const difference_type& n, const random_access_iterator& ref)
            {
                return (ref.base() + n);
            }

			bool operator==(const random_access_iterator &ref) const {
                return (base() == ref.base());
            }

            bool operator!=(const random_access_iterator &ref) const {
                return ((base() != ref.base()));
            }

            bool operator<(const random_access_iterator &ref) const {
                return (base() < ref.base());
            }

			bool operator<=(const random_access_iterator &ref) const {
                return (base() <= ref.base());
            }

			bool operator>(const random_access_iterator &ref) const {
                return (base() > ref.base());
            }

			bool operator>=(const random_access_iterator &ref) const {
                return (base() >= ref.base());
            }
			
			reference operator*() const {
				return (*this->_ptr);
			}

			pointer operator->() const {
				return (&(*this->_ptr));
			}

			reference operator[](const difference_type &n) const {
				return (this->_ptr[n]);
			}
			
		private:
			pointer _ptr;
	};

	template <class Ite1, class Ite2>
	bool	operator!=(random_access_iterator<Ite1> &lhs, random_access_iterator<Ite2> &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Ite1, class Ite2>
	bool	operator!=(const random_access_iterator<Ite1> &lhs, const random_access_iterator<Ite2> &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Ite1, class Ite2>
	bool	operator==(random_access_iterator<Ite1> &lhs, random_access_iterator<Ite2> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Ite1, class Ite2>
	bool	operator==(const random_access_iterator<Ite1> &lhs, const random_access_iterator<Ite2> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Ite1, class Ite2>
	bool	operator<(const random_access_iterator<Ite1> &lhs, const random_access_iterator<Ite2> &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Ite1, class Ite2>
	bool	operator<=(const random_access_iterator<Ite1> &lhs, const random_access_iterator<Ite2> &rhs) {
		return (lhs.base() <= rhs.base());
	}
	
	template <class Ite1, class Ite2>
	bool	operator>(const random_access_iterator<Ite1> &lhs, const random_access_iterator<Ite2> &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Ite1, class Ite2>
	bool	operator>=(const random_access_iterator<Ite1> &lhs, const random_access_iterator<Ite2> &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Ite1, class Ite2>
	ptrdiff_t operator-(const random_access_iterator<Ite1> &lhs, const random_access_iterator<Ite2> &rhs) {
		return (lhs.base() - rhs.base());
	}

	template <class Ite>
	ptrdiff_t	itlen(Ite first, Ite last) {
		ptrdiff_t	i = 0;

		while (first != last)
		{
			++first;
			++i;
		}
		return (i);
	}
}

#endif