#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "list_node.hpp"
#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include <limits>

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
				delete _before_node;
				delete _after_node;
			};
//			operator=
			list &operator=(const list<T> &other) {
				if (*this == other)
					return (*this);
				clear();
				assign(other.begin(), other.end());
				return (*this);
			}
//			Iterators:
			iterator begin(){
				if (_length == 0)
					return iterator(_after_node->prev);
				return iterator(_before_node->next);
			};
			const_iterator begin() const {
				return const_iterator(_before_node->next);
			};
			iterator end() {
				return iterator(_after_node);
			};
			const_iterator end() const {
				return const_iterator (_after_node);
			}
//			Capacity:
			bool empty() const	{return (!_length);};
			size_type size() const {return (_length);};
			size_type max_size() const {
				return (std::numeric_limits<size_type>::max() / (sizeof(node)));
			};
//			Element access:
			reference front() {return _before_node->next->data;};
			const_reference front() const {return _before_node->next->data;};
			reference back() {return _after_node->prev->data;};
			const_reference back() const {return _after_node->prev->data;};
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
				while (n--)
					push_back(val);
			};
			void push_back (const value_type& val) {
				node *tmp = new node(val);
				tmp->prev = _after_node->prev;
				tmp->next = _after_node;
				tmp->prev->next = tmp;
				_after_node->prev = tmp;
				_length++;
			};
			void pop_back() {
				node *tmp = _after_node->prev;
				_after_node->prev = _after_node->prev->prev;
				_after_node->prev->next = _after_node;
				delete tmp;
				_length -= 1;
			};
			void push_front (const value_type& val){
				node *tmp = new node(val);
				tmp->prev = _before_node;
				tmp->next = _before_node->next;
				_before_node->next->prev = tmp;
				_before_node->next = tmp;
				_length += 1;
			};
			void pop_front(){
				node *tmp = _before_node->next;
				_before_node->next->prev = _before_node;
				_before_node->next = _before_node->next->next;
				delete tmp;
				_length -= 1;
			};
			void clear(){
				while(_length)
					pop_back();
			}
//			single element (1)
			iterator insert (iterator position, const value_type& val){
				node *p = position._p;
				node *tmp = new node(val);

				tmp->prev = p->prev;
				p->prev->next = tmp;
				tmp->next = p;
				p->prev = tmp;
				_length += 1;
				return (tmp);
			};
//			fill (2)
			void insert (iterator position, size_type n, const value_type& val){
				while(n--)
					insert(position, val);
			};
//			range (3)
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last){
				for( ;first != last; first++)
					insert(position, *first);
			};
			iterator erase (iterator position){
				node *tmp = position._p;
				position++;
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;

				delete tmp;
				_length -= 1;
				return position;
			};
			iterator erase (iterator first, iterator last){
				for ( ; first != last; first++)
					erase(first);
				return (last);
			};
			void swap (list& x){
				ft::swap(_before_node->next, x._before_node->next);
				ft::swap(_before_node->prev, x._before_node->prev);
				ft::swap(_after_node->next, x._after_node->next);
				ft::swap(_after_node->prev, x._after_node->prev);
				ft::swap(_length, x._length);
			};
			void resize (size_type n, value_type val = value_type()){
				while (n < _length)
					push_back(val);
				while (n > _length)
					pop_back();
			};
	};
}

#endif //FT_CONTAINERS_LIST_HPP
