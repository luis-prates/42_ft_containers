/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:38:58 by lprates           #+#    #+#             */
/*   Updated: 2022/12/19 22:56:14 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
	typedef T	type;
};

template <class T, T val>
struct integral_constant {
	static const T						value = val;
	typedef T							value_type;
	typedef integral_constant<T, val>	type;
	
	operator value_type() const { return (value); }
};

typedef integral_constant<bool, false> false_type;
typedef integral_constant<bool, true> true_type;

template <class T>
struct is_integral : public false_type {};

template <class T>
struct is_integral<const T> : public is_integral<T> {};

template <class T>
struct is_integral<volatile const T> : public is_integral<T> {};

template <class T>
struct is_integral<volatile T> : public is_integral<T> {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<unsigned short> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<unsigned long> : public true_type {};

template <>
struct is_integral<signed char> : public true_type {};

template <>
struct is_integral<short> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<long> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<wchar_t> : public true_type {};

#endif