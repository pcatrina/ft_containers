#ifndef FT_CONTAINERS_VECTOR_ALLOCATOR_HPP
#define FT_CONTAINERS_VECTOR_ALLOCATOR_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

namespace ft {
	template < class T, class Alloc = std::allocator<T> > class vector {
	public:
		typedef T							value_type;
		typedef Alloc						allocator_type;
		typedef typename allocator_type::reference 	reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer 	pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef random_access_iterator<value_type> iterator;
		typedef random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const iterator> const_reverse_iterator;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t 	size_type;
	private:
		allocator_type 		_alloc;
		pointer				_alloc_start;
		size_type 			_size;
		size_type			_capacity;
	public:
		explicit vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0) {};
		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0) {
			assign(n, val);
		};
		template <class InputIterator> vector (InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator_type(),
		typename enable_if<is_input_iterator<InputIterator>::value>::type* = 0) :_alloc(alloc), _size(0),
				_capacity(0) {
			assign(first, last);
		};
		vector (const vector& x): _alloc(x._alloc), _size(0), _capacity(0){
			assign(x.begin(), x.end());
		};
		~vector() {
			clear();
			if (_capacity)
				_alloc.deallocate(_alloc_start, _capacity);
		};
		vector& operator= (const vector& x) {
			if (this == &x)
				return *this;
			clear();
			assign(x.begin(), x.end());
			return *this;
		};
//		Iterators ft::vector
		iterator begin() {
			return iterator(_alloc_start);
		};
		const_iterator begin() const {
			return const_iterator(_alloc_start);
		};
		iterator end() {
			return iterator(_alloc_start+_size);
		};
		const_iterator end() const {
			return const_iterator(_alloc_start+_size);
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
				pointer tmp = _alloc.allocate(n);
				std::memcpy(tmp, _alloc_start, _size * sizeof(value_type));
				for (size_type i = 0; i != _size; ++i)
					_alloc.destroy(_alloc_start + i);
				if (_capacity)
					_alloc.deallocate(_alloc_start, _capacity);
				_alloc_start = tmp;
				_capacity = n;
			}
		};
//		Element access:
		reference operator[] (size_type n) {
			return _alloc_start[n];
		};
		const_reference operator[] (size_type n) const {
			return _alloc_start[n];
		};
		reference at (size_type n) {
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _alloc_start[n];
		};
		const_reference at (size_type n) const {
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _alloc_start[n];
		};
		reference front() {return _alloc_start[0];};
		const_reference front() const {return _alloc_start[0];};
		reference back() {return _alloc_start[_size - 1];};
		const_reference back() const {return _alloc_start[_size - 1];};
//		Modifiers:
//		range
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
					 typename enable_if<is_input_iterator<InputIterator>::value>::type* = 0) {
			clear();
			size_type n = 0;
			InputIterator tmp = first;
			for (;tmp != last;++tmp)
				++n;
			reserve(n);
			tmp = first;
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
			_alloc.construct(_alloc_start + _size, val);
//			_alloc_start[_size] = val;
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
			return iterator(_alloc_start + i);
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
				position = iterator(_alloc_start + i);
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
		void insert (iterator position, InputIterator first, InputIterator last,
					 typename enable_if<is_input_iterator<InputIterator>::value>::type* = 0) {
			size_type  n = 0;
			for (InputIterator it = first; it != last; ++it)
				++n;
			size_type  i = 0;
			for (iterator it = begin(); it != position; ++it)
				++i;
			if (_size + n > _capacity) {
				if (_size + n > _capacity * 2)
					reserve(_size + n);
				else
					reserve(_capacity * 2);
				position = iterator(_alloc_start + i);
			}
			std::memmove(position._p + n, position._p, (_size - i) * sizeof(value_type));
			_size += n;
			while (n--){
				*position = *first;
				++position;
				++first;
			}
		};
		iterator erase (iterator position) {
			return erase(position, position + 1);
		};
		iterator erase (iterator first, iterator last) {
			for (; last != end(); ++last, ++first) {
				*first = *last;
			}
			iterator it = first;
			for (;it != last; ++it)
				--_size;
			return first;
		};
		void swap (vector& x) {
			if (this != &x) {
				ft::swap(_size, x._size);
				ft::swap(_alloc_start, x._alloc_start);
				ft::swap(_capacity, x._capacity);
			}
		};
		void clear() {
			if (_size > 0) {
				for (size_type i = 0; i != _size; ++i)
					_alloc.destroy(_alloc_start + i);
				_size = 0;
			}
		};
	};
//	(1)
	template <class T>
	bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename vector<T>::const_iterator lit = lhs.begin();
		typename vector<T>::const_iterator rit = rhs.begin();
		for(; lit != lhs.end(); ++lit, ++rit) {
			if (*lit != *rit)
				return false;
		}
		return true;
	};
//	(2)
	template <class T>
	bool operator!= (const vector<T>& lhs, const vector<T>& rhs) {
		return !(lhs==rhs);
	};
//	(3)
	template <class T>
	bool operator<  (const vector<T>& lhs, const vector<T>& rhs) {
		typename vector<T>::const_iterator lit = lhs.begin();
		typename vector<T>::const_iterator rit = rhs.begin();
		for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
			if (*lit < *rit)
				return true;
			else if (*rit < *lit)
				return false;
		}
		return (rit != rhs.end());
	};
//	(4)
	template <class T>
	bool operator<= (const vector<T>& lhs, const vector<T>& rhs) {
		return !(rhs < lhs);
	};
//	(5)
	template <class T>
	bool operator>  (const vector<T>& lhs, const vector<T>& rhs) {
		return !(lhs <= rhs);
	};
//	(6)
	template <class T>
	bool operator>= (const vector<T>& lhs, const vector<T>& rhs) {
		return !(lhs < rhs);
	};
//	swap
	template <class T>
	void swap (vector<T>& x, vector<T>& y) {
		x.swap(y);
	};
}

#endif //FT_CONTAINERS_VECTOR_ALLOCATOR_HPP
