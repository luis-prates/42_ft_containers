/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:40:52 by lprates           #+#    #+#             */
/*   Updated: 2022/12/19 00:43:10 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EQUAL_HPP
# define FT_EQUAL_HPP

namespace ft {
	template <class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
        for (; first1 != last1; first1++, first2++)
            if (!(*first1 == *first2))
                return (false);
        return (true);
    }

    template <class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
        for (; first1 != last1; first1++, first2++)
            if (!p(*first1, *first2))
                return (false);
        return (true);
    }
}

#endif