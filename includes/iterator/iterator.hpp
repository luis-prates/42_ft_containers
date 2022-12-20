/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:56:08 by lprates           #+#    #+#             */
/*   Updated: 2022/12/20 02:08:46 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "iterator_traits.hpp"

namespace ft {
	template <typename T>
	class iterator {
		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T								*pointer;
			typedef T								&reference;
			typedef ft::random_access_iterator_tag	iterator_category;

			iterator() : _ptr(NULL) {}

			iterator(pointer ptr) : _ptr(ptr) {}
			
			iterator(const iterator &ref) : _ptr(ref._ptr) {}

			virtual ~iterator() {}

			iterator &operator=(const iterator &ref) {
				if (this != &ref)
					_ptr = ref._ptr;
				return (*this);
			}

			operator iterator<const value_type>() const {
				return iterator<const value_type>(_ptr);
			}

			iterator &operator--() {
				--_ptr;
				return (*this);
			}

			iterator &operator--(int) {
				iterator it(*this);
				operator--();
				return (it);
			}

			iterator &operator-=(const difference_type &n) {
				_ptr -= n;
				return (*this);
			}

			iterator &operator-(const difference_type &n) const {
				iterator it(*this);
				it -= n;
				return (it);
			}

			difference_type operator-(const iterator &ref) const {
				return (_ptr - ref._ptr);
			}

			iterator &operator++() {
				++_ptr;
				return (*this);
			}

			iterator operator++(int) {
				iterator it(*this);
				operator++();
				return (it);
			}

			iterator &operator+=(const difference_type &n) {
				_ptr += n;
				return (*this);
			}

			iterator operator+(const difference_type &n) const {
				iterator it(*this);
				it += n;
				return (it);
			}

			// have to check the friend operator+ function
			/*iterator operator+(const difference_type& n, const iterator& ref)
            {
                return (ref + n);
            }*/

			bool operator==(const iterator& ref) const {
                return (_ptr == ref._ptr);
            }

            bool operator!=(const iterator& ref) const {
                return (!(_ptr == ref._ptr));
            }

            bool operator<(const iterator& ref) const {
                return (_ptr < ref._ptr);
            }

			bool operator<=(const iterator& ref) const {
                return (_ptr <= ref._ptr);
            }

			bool operator>(const iterator& ref) const {
                return (_ptr > ref._ptr);
            }

			bool operator>=(const iterator& ref) const {
                return (_ptr >= ref._ptr);
            }
			
			reference operator*() const {
				return (*_ptr);
			}

			pointer operator->() const {
				return (_ptr);
			}

			reference operator[](const difference_type &n) const {
				return (_ptr[n]);
			}
			
		private:
			T* _ptr;
	};
}

#endif