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
	private:
		value_type*	_arr;
		size_type 	_size;
		size_type	_capacity;
	public:
		explicit vector(): _arr(NULL), _size(0), _capacity(0) {};
		explicit vector (size_type n, const value_type& val = value_type()): _arr(NULL), _size(0), _capacity(0) {
			assign(n, val);
		};
		template <class InputIterator> vector (InputIterator first, InputIterator last)
		:_arr(NULL), _size(0), _capacity(0) {
			assign(first, last);
		};
		vector (const vector& x): _arr(NULL), _size(0), _capacity(0)
		{};
		~vector() {delete[] _arr;};
//		range
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			clear();
			size_type n = 0;
			InputIterator tmp = first;
			for (;tmp != last;++tmp)
				++n;
			reserve(n);
			for (; tmp != last; ++tmp)
				push_back(*tmp);
		};
//		fill
		void assign (size_type n, const value_type& val) {
			clear();
			while(n--)
				push_back(val);
		};
		void push_back (const value_type& val) {
			if (_size + 1 > _capacity) {
				if (_capacity == 0)
					reserve(1);
				else
					reserve(_capacity * 2);
			}
			_arr[_size] = val;
			++_size;
		};
		void reserve (size_type n) {
			if (n > _capacity) {
				value_type* tmp = new value_type[n];
				std::memcpy(tmp, _arr, _size * sizeof(value_type));
				delete [] _arr;
				_arr = tmp;
				_capacity = n;
			}
		};
		void clear() {
			delete [] _arr;
			_size = 0;
			_arr = new value_type[_capacity];
		};
	};
}

#endif //FT_CONTAINERS_VECTOR_HPP
