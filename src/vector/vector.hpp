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
		typedef random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const iterator> const_reverse_iterator;
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
		{
			value_type* tmp = new value_type[x._size];
			std::memcpy(tmp, x._arr, x._size* sizeof(value_type));
			_arr = tmp;
			_capacity = x._capacity;
			_size = x._size;
		};
		~vector() {delete[] _arr;};
		vector& operator= (const vector& x) {
			if (this == &x)
				return *this;
			clear();
			assign(x.begin(), x.end());
			return *this;
		};
//		Iterators ft::vector
		iterator begin() {
			return iterator(_arr);
		};
		const_iterator begin() const {
			return const_iterator(_arr);
		};
		iterator end() {
			return iterator(_arr+_size);
		};
		const_iterator end() const {
			return const_iterator(_arr+_size);
		};
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		};
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		};
		reverse_iterator rend() {
			return reverse_iterator(begin());
		};
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		};
//		Capacity ft::vector
		size_type size() const {return _size;};
		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / sizeof(value_type));
		};
		void resize (size_type n, value_type val = value_type()) {
			if (n > _capacity * 2)
				reserve(n);
			else if (n > _capacity)
				reserve(_capacity * 2);
			while (n > _size)
				push_back(val);
			while (n < _size)
				pop_back();
		};
		size_type capacity() const {return _capacity;};
		bool empty() const {
			if (_size)
				return false;
			return true;
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
//		Element access:
		reference operator[] (size_type n) {
			return _arr[n];
		};
		const_reference operator[] (size_type n) const {
			return _arr[n];
		};
		reference at (size_type n) {
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _arr[n];
		};
		const_reference at (size_type n) const {
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _arr[n];
		};
		reference front() {return _arr[0];};
		const_reference front() const {return _arr[0];};
		reference back() {return _arr[_size - 1];};
		const_reference back() const {return _arr[_size - 1];};
//		Modifiers:
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
		void pop_back() {
			if (_size > 0)
				--_size;
		};
//		single element (1)
		iterator insert (iterator position, const value_type& val) {
			size_type i = 0;
			for (iterator it = begin(); it != position; ++it)
				++i;
			insert(position, 1, val);
			return iterator(_arr + i);
		};
//		fill (2)
		void insert (iterator position, size_type n, const value_type& val) {
			size_type i = 0;
			for (iterator it = begin(); it != position; ++it)
				++i;
			if (_size + n > _capacity) {
				if (_size + n > _capacity * 2)
					reserve(_size + n);
				else
					reserve(_capacity * 2);
			}
			std::memmove(position._p + n, position._p, (_size - i) * sizeof(value_type));
			_size += n;
			while(n--){
				*position = val;
				++position;
			}
		};
//		range (3)
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last) {
			size_type  n = 0;
			for (InputIterator it = first; it != last; ++it)
				++n;
			size_type  i = 0;
			for (InputIterator it = begin(); it != position; ++it)
				++i;
			if (_size + n > _capacity) {
				if (_size + n > _capacity * 2)
					reserve(_size + n);
				else
					reserve(_capacity * 2);
			}
			std::memmove(position._p + n, position._p, (_size - i) * sizeof(value_type));
			_size += n;
			while (n--){
				*position = *first;
				++position;
				++first;
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
