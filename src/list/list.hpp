#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

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
			return iterator(_init_node);
		};
		const_iterator end() const {
			return const_iterator (_init_node);
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
//		entire list (1)
		void splice (iterator position, list& x) {
			splice(position, x, x.begin(), x.end());
		};
//		single element (2)
		void splice (iterator position, list& x, iterator i) {
			splice(position, x, i, i);
		};
//		element range (3)
		void splice (iterator position, list& x, iterator first, iterator last) {
			if (*this == x)
				return;
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
			while (f != p) {
				--x._length;
				++_length;
				f = f->next;
			}
		};
		void remove (const value_type& val) {
			 remove_if(ft::const_pred<value_type>(val));
		};
		template <class Predicate>
		void remove_if (Predicate pred) {
			for (iterator it = begin(); it != end(); )
			{
				if (pred(*it))
				{
					iterator tmp = it;
					++it;
					erase(tmp);
				}
				else
					++it;
			}
		};
		void unique(){
			unique(ft::binary_pred<value_type>());
		};
		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred){
			if (empty())
				return;
			for(iterator prev = begin(), next = ++begin(); next != end();){
				if (binary_pred(*prev, *next)) {
					iterator tmp = next;
					++next;
					erase(tmp);
				}
				else {
					++prev;
					++next;
				}
			}
		};
//		(1)
		void merge (list& x) {
			merge(x, ft::less<value_type>());
		};
//		(2)
		template <class Compare> void merge (list& x, Compare comp) {
			if (*this == x)
				return;
			iterator m_it = begin(),  x_it = x.begin();
			for (; m_it != end() && x_it != x.end();) {
				if (comp(x_it, m_it)) {
					iterator tmp = x_it;
					++x_it;
					splice(m_it, x, tmp);
				}
				else
					++m_it;
			}
			splice(m_it, x, x_it, x.end());
		};
		void sort() {
			sort(ft::less<value_type>());
		};
		template< class Compare >void sort( Compare comp ) {
			if (empty())
				return;
//Place for sort list -->
		};
	};
//	relational operators
	template <class T> bool operator== (const list<T>& lhs, const list<T>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (typename list<T>::iterator l_it = lhs.begin(), r_it = rhs.begin(); l_it != lhs.end(); ++l_it, ++r_it){
			if (!(*l_it == *r_it))
				return false;
		}
		return true;
	}
	template <class T> bool operator!= (const list<T>& lhs, const list<T>& rhs){
		return !(lhs == rhs);
	}
	template <class T> bool operator<  (const list<T>& lhs, const list<T>& rhs){
		typename list<T>::iterator l_it = lhs.begin(), r_it = rhs.begin();
		for (; l_it != lhs.end() && r_it != rhs.end(); ++l_it, ++r_it){
			if (*l_it < *r_it)
				return true;
			else if (*l_it > *r_it)
				return false;
		}
		return (r_it != rhs.end());
	}
	template <class T> bool operator<= (const list<T>& lhs, const list<T>& rhs) {
		return (!(lhs < rhs));
	}
	template <class T> bool operator>  (const list<T>& lhs, const list<T>& rhs) {
		return (rhs < lhs);
	}
	template <class T> bool operator>= (const list<T>& lhs, const list<T>& rhs) {
		return (!(rhs < lhs));
	}
}

#endif //FT_CONTAINERS_LIST_HPP
