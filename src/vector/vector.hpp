#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

namespace ft {
	template< class T> class vector {
	public:
		typedef T				value_type;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef random_access_iterator<value_type> iterator;
		typedef const random_access_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef const ft::reverse_iterator<iterator> const_reverse_iterator;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t 	size_type;
	};
}

#endif //FT_CONTAINERS_VECTOR_HPP
