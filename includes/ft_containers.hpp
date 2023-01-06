/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_containers.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:37:49 by lprates           #+#    #+#             */
/*   Updated: 2023/01/06 20:40:36 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_HPP
# define FT_CONTAINERS_HPP

# ifndef FT
#  define FT 1	// 0 == Tests the original containers
				// 1 == Tests my containers
# endif

# if FT // using ft library
//# include "stack.hpp"
#  include "vector.hpp"
#  include "map.hpp"
#  include "stack.hpp"
#  include "iterator/iterator.hpp"
#  include "utils/pairs.hpp"
# else // using std library
#  include <algorithm>
#  include <cstddef>
#  include <iterator>
#  include <map>
#  include <stack>
#  include <utility>
#  include <vector>
   namespace ft = std;
#endif

#endif /* FT_CONTAINERS_HPP */