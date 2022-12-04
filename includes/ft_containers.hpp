/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_containers.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:37:49 by lprates           #+#    #+#             */
/*   Updated: 2022/12/04 22:49:03 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_HPP
#define FT_CONTAINERS_HPP

#define FT  0
#define STD 1

#ifndef LIB
# define LIB FT
// # define LIB STD
#endif /* LIB */

#if LIB == FT // using ft library
//# include "stack.hpp"
# include "vector.hpp"
// #  include "map.hpp"
# include "iterator.hpp"
//# include "utils.hpp"
#elif LIB == STD // using std library
# include <algorithm>
# include <cstddef>
# include <iterator>
# include <map>
# include <stack>
# include <utility>
# include <vector>
namespace ft = std;
#endif /* LIB */

#endif /* FT_CONTAINERS_HPP */