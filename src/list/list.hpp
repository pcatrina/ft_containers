#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "list_node.hpp"
#include "../common/utils.hpp"
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
			typedef list_node<typename ft::remove_const<value_type>::type> node;

//
		private:
			node*	_before_node;
			node*	_after_node;
			size_type		_length;

		public:
//			default (1)
			explicit list () : _length(0), _before_node(nullptr), _after_node(nullptr) {
				_before_node = new list_node<T>;
				_after_node = new list_node<T>;
				_before_node->next = _after_node;
				_after_node->prev = _before_node;
			};
//			fill (2)
			explicit list (size_type n, const value_type  &data = value_type()) : _length(0),
				_before_node(nullptr), _after_node(nullptr) {
				_before_node = new list_node<T>;
				_after_node = new list_node<T>;
				_before_node->next = _after_node;
				_after_node->prev = _before_node;

				assign(n, data);
			};
//			range (3)
			template <class InputIterator>
			list (InputIterator _begin, InputIterator _end) : _before_node(nullptr), _after_node(nullptr),
				_length(0) {
				_before_node = new list_node<T>;
				_after_node = new list_node<T>;
				_before_node->next = _after_node;
				_after_node->prev = _before_node;

				assign(_begin, _end);
			};
//			copy (4)
			list(const list &other) : _before_node(nullptr), _after_node(nullptr), _length(0) {
				_before_node = new list_node<T>;
				_after_node = new list_node<T>;
				_before_node->next = _after_node;
				_after_node->prev = _before_node;

				*this = other;
			};
//			Destructor
			~list() {
				clear();
			};
//			operator=
			list &operator=(const list<T> &other) {
				if (*this == other)
					return (*this);
//				clear()
//				assign(other.begin(), other.end());
				return (*this);
			}
//			Modifiers:
//			range (1)
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				clear();

				for(; first != last; first++)
					push_back(*first);
			};
			void assign (size_type n, const value_type& val){
				clear();

				while (--n)
					push_back(val);
			};
			void push_back (const value_type& val) {
				node *tmp = new node(val);

				tmp->prev = _after_node->prev;
				tmp->next = _after_node;
				_after_node->prev = tmp;
				_length += 1;
			};
			void pop_back() {
				node *tmp = _after_node->prev;
				_after_node = _after_node->prev->prev;
				_after_node->prev->next = _after_node;
				delete tmp;
				_length -= 1;
			};
			void clear(){
				while(_length)
					pop_back();
			}
	};
}

#endif //FT_CONTAINERS_LIST_HPP
