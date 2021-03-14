#ifndef FT_CONTAINERS_DEQUE_HPP
#define FT_CONTAINERS_DEQUE_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

namespace ft {
	template < class T> class deque {
	public:
		typedef T				value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef random_access_iterator<value_type> iterator;
		typedef random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const iterator> const_reverse_iterator;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t 	size_type;
	private:
		pointer* _cntr;
		size_type _capacity;
		size_type _start;
		size_type _size;
	public:
		explicit deque (const allocator_type& alloc = allocator_type())
			: _cntr(NULL), _capacity(0), _start(0), _size(0) {};
		explicit deque (size_type n, const value_type& val = value_type())
			: _cntr(NULL), _capacity(0), _start(0), _size(0) {};
	};
}

#endif //FT_CONTAINERS_DEQUE_HPP
