/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:41:20 by lprates           #+#    #+#             */
/*   Updated: 2022/12/20 01:46:57 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft {
	
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/*template<typename _Category, typename _T, typename _Distance = ptrdiff_t,
           typename _Pointer = _T*, typename _Reference = _T&>
    struct iterator
    {
      typedef _Category		iterator_category;
      typedef _T			value_type;
      typedef _Distance		difference_type;
      typedef _Pointer		pointer;
      typedef _Reference	reference;
    };*/

	template <typename Iterator>
	class iterator_traits {
		public:
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	class iterator_traits<T*> {
		public:
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T								*pointer;
			typedef T								&reference;
			typedef random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	class iterator_traits<const T*> {
		public:
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const T							*pointer;
			typedef const T							&reference;
			typedef random_access_iterator_tag		iterator_category;
	};
}

#endif