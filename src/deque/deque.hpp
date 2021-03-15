#ifndef FT_CONTAINERS_DEQUE_HPP
#define FT_CONTAINERS_DEQUE_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

namespace ft {
	template < class T, class Alloc = std::allocator<T> > class deque {
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
		size_type 			_size;
		size_type 			_capacity;
		pointer				_alloc_start;

		void reserve(size_type n) {
			if (n > _capacity) {
				pointer tmp = _alloc.allocate(n);
				std::memcpy(tmp, _alloc_start, _size * sizeof(value_type));
				clear();
				if (_capacity)
					_alloc.deallocate(_alloc_start, _capacity);
				_alloc_start = tmp;
				_capacity = n;
			}
 		}
	public:
		explicit deque (const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0) {
			_alloc_start = _alloc.allocate(0);
		};
		explicit deque (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0){
			assign(n, val);
		};
		template <class InputIterator> deque (InputIterator first, InputIterator last,
			   const allocator_type& alloc = allocator_type(), typename
			   enable_if<is_input_iterator<InputIterator>::value>::type* = 0): _alloc(alloc), _size(0), _capacity(0) {
			assign(first, last);
		};
		deque (const deque& x): _alloc(x._alloc), _size(0), _capacity(0) {
			assign(x.begin(), x.end());
		};
		~deque() {
			clear();
			_alloc.deallocate( _alloc_start, _capacity);};
//		Iterators:
		iterator begin() {return iterator (_alloc_start);};
		const_iterator begin() const { return iterator (_alloc_start);};
		iterator end() {return iterator(_alloc_start+_size);};
		const_iterator end() const {return const_iterator(_alloc_start+_size);};
		reverse_iterator rbegin() {return reverse_iterator(end());};
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());};
		reverse_iterator rend() {return reverse_iterator(begin());};
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());};
//		Capacity:
		size_type size() const {return _size;};
		size_type max_size() const {return (std::numeric_limits<size_type>::max() / sizeof(value_type));};
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
		bool empty() const {return !_size;};
//		Element access:
		reference operator[] (size_type n) { return (_alloc_start[n]); };
//		Modifiers:
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
			   typename enable_if<is_input_iterator<InputIterator>::value>::type* = 0) {
			clear();
			size_type n = 0;
			InputIterator tmp = first;
			for (; tmp != last; ++tmp)
				++n;
			reserve(n);
			tmp = first;
			for (; tmp != last; ++tmp)
				push_back(*tmp);
		};
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
			_alloc_start[_size] = val;
			++_size;
		};
		void pop_back() {
			if (_size > 0)
				--_size;
		};
		void clear() {
			if (_size)
				for (size_type i = 0; i != _size; ++i)
					_alloc.destroy(_alloc_start + i);
		};
	};
}

#endif //FT_CONTAINERS_DEQUE_HPP
