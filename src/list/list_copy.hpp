#ifndef FT_CONTAINERS_LIST_COPY_HPP
#define FT_CONTAINERS_LIST_COPY_HPP

#include "list_node.hpp"
#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

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
		typedef ft::reverse_iterator<iterator>	reverse_iterator;
		typedef const ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t 				difference_type;
		typedef std::size_t 				size_type;
		typedef list_node<typename ft::remove_const<value_type>::type> node;
	private:
		node*			_init_node;
		size_type		_length;
	public:
//			default (1)
		explicit list () : _init_node(nullptr), _length(0) {
			_init_node = new list_node<T>;
			_init_node->next = _init_node;
			_init_node->prev = _init_node;
		};
//			fill (2)
		explicit list (size_type n, const value_type  &data = value_type()) : _length(0), _init_node(nullptr) {
			_init_node = new list_node<T>;
			_init_node->next = _init_node;
			_init_node->prev = _init_node;
			assign(n, data);
		};
//			range (3)
		template <class InputIterator>
		list (InputIterator _begin, InputIterator _end) : _init_node(nullptr), _length(0) {
			_init_node = new list_node<T>;
			_init_node->next = _init_node;
			_init_node->prev = _init_node;
			assign(_begin, _end);
		};
//			copy (4)
		list(const list &other) : _init_node(nullptr), _length(0) {
			_init_node = new list_node<T>;
			_init_node->next = _init_node;
			_init_node->prev = _init_node;

			*this = other;
		};
//			Destructor
		~list() {
			clear();
			delete _init_node;
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
				return end();
			return iterator(_init_node->next);
		};
		const_iterator begin() const {
			return const_iterator(_init_node->next);
		};
		iterator end() {
			return iterator(_init_node->prev);
		};
		const_iterator end() const {
			return const_iterator (_init_node->prev);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(_init_node->prev);
		};
		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(_init_node->prev);
		};
		reverse_iterator rend() {
			return reverse_iterator(_init_node->next);
		};
		const_reverse_iterator rend() const {
			return const_reverse_iterator (_init_node->next);
		};
//			Capacity:
		bool empty() const	{return (!_length);};
		size_type size() const {return (_length);};
		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / (sizeof(node)));
		};
//			Element access:
		reference front() {return _init_node->next->data;};
		const_reference front() const {return _init_node->next->data;};
		reference back() {return _init_node->prev->data;};
		const_reference back() const {return _init_node->prev->data;};
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
			tmp->prev = _init_node->prev;
			tmp->next = _init_node;
			tmp->prev->next = tmp;
			_init_node->prev = tmp;
			_length++;
		};
		void pop_back() {
			node *tmp = _init_node->prev;
			_init_node->prev = _init_node->prev->prev;
			_init_node->prev->next = _init_node;
			delete tmp;
			_length -= 1;
		};
		void push_front (const value_type& val){
			node *tmp = new node(val);
			tmp->prev = _init_node;
			tmp->next = _init_node->next;
			_init_node->next->prev = tmp;
			_init_node->next = tmp;
			_length += 1;
		};
		void pop_front(){
			node *tmp = _init_node->next;
			_init_node->next->prev = _init_node;
			_init_node->next = _init_node->next->next;
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
			ft::swap(_init_node->next, x._init_node->next);
			ft::swap(_init_node->prev, x._init_node->prev);
			ft::swap(_length, x._length);
		};
		void resize (size_type n, value_type val = value_type()){
			while (n < _length)
				push_back(val);
			while (n > _length)
				pop_back();
		};
		void splice (iterator position, list& x, iterator first, iterator last) {
//			if (*this == x)
//				return;
			node *f = first._p;
			node *l = last._p;
			node *p = position._p;

			node *before = f->prev;

			f->prev = p->prev;
			f->prev->next = f;
			p->prev = l->prev;
			p->prev->next = p;

			before->next = l;
			l->prev = before;
			while (f != p)
			{
				--x._length;
				++_length;
				f = f->next;
			}
		};
	};
}

#endif //FT_CONTAINERS_LIST_COPY_HPP
