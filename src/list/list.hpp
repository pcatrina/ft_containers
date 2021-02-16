#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "../common/utils.hpp"
#include "list_node.hpp"
#include "../common/iterators.hpp"

namespace ft {
	template < class T >
		class list {
		public:
			typedef T							value_type;
			typedef T& 							reference;
			typedef const T&					const_reference;
			typedef T*							pointer;
			typedef const T*					const_pointer;
			typedef	list_iterator<value_type>	iterator;
			typedef const list_iterator<value_type> const_iterator;
			typedef std::ptrdiff_t 				difference_type;
			typedef std::size_t 				size_type;
//
		private:
			list_node<T>*	_before_node;
			list_node<T>*	_after_node;
			size_type		_length;

		public:
//			default (1)
			explicit list () : _length(0), _before_node(nullptr), _after_node(nullptr) {
				_before_node = new list_node<T>;
				_after_node = new list_node<T>;
				_before_node->next = _after_node;
				_after_node->prev = _before_node;
			}
//			fill (2)
			explicit list (size_type n, const value_type  &data = value_type()) : _length(0),
				_before_node(nullptr), _after_node(nullptr) {
				_before_node = new list_node<T>;
				_after_node = new list_node<T>;
				_before_node->next = _after_node;
				_after_node->prev = _before_node;
			}
//			range (3)
			template <class InputIterator>
			list (InputIterator _begin, InputIterator _end) : _before_node(nullptr), _after_node(nullptr),
				_length(0) {
				_before_node = new list_node<T>;
				_after_node = new list_node<T>;

				_before_node->next = _after_node;
				_after_node->prev = _before_node;
			}
//			copy (4)
			list (const list& x) {

			}


	};
}

#endif //FT_CONTAINERS_LIST_HPP
