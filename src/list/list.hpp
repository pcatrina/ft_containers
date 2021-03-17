#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "list_node.hpp"
#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

namespace ft {
	template < class T, class Alloc = std::allocator<T> > class list {
	public:
		typedef T									value_type;
		typedef Alloc							allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer	pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef	bidirectional_iterator<value_type>	iterator;
		typedef bidirectional_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator>	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t 				difference_type;
		typedef std::size_t 				size_type;
		typedef list_node<typename ft::remove_const<value_type>::type> node;
	private:
		typedef typename allocator_type::template
		rebind<list_node<T> >::other node_alloc;
		typedef typename node_alloc::pointer	_node_pointer;
		node_alloc		_node_alloc;
		allocator_type  _alloc;
		node*			_init_node;
		size_type		_length;
//		CreateNode
		_node_pointer CreateNode (const T& data, list_node<T>*prev = nullptr, list_node<T>*next = nullptr) {
			_node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, list_node<T>(data));
			new_node->prev = prev;
			new_node->next = next;
			return (new_node);
		}
	public:
//			default (1)
		explicit list (const allocator_type& alloc = allocator_type()): _alloc(alloc), _init_node(nullptr), _length(0) {
			_init_node = _node_alloc.allocate(1);
			_node_alloc.construct(_init_node, list_node<value_type>());
			_init_node->next = _init_node;
			_init_node->prev = _init_node;
		};
//			fill (2)
		explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc =
				allocator_type()) :_alloc(alloc), _init_node(nullptr), _length(0) {
			_init_node = _node_alloc.allocate(1);
			_node_alloc.construct(_init_node, list_node<value_type>());
			_init_node->next = _init_node;
			_init_node->prev = _init_node;
			assign(n, val);
		};
//			range (3)
		template <class InputIterator>
		list (InputIterator _begin, InputIterator _end,
			typename enable_if<is_input_iterator<InputIterator>::value>::type* = 0): _init_node(nullptr), _length(0) {
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
			if (_length == 0)
				return end();
			return const_iterator(_init_node->next);
		};
		iterator end() {
			return iterator(_init_node);
		};
		const_iterator end() const {
			return const_iterator (_init_node);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		};
		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(end());
		};
		reverse_iterator rend() {
			return reverse_iterator(begin());
		};
		const_reverse_iterator rend() const {
			return const_reverse_iterator (begin());
		};
//			Capacity:
		bool empty() const	{return (!_length);};
		size_type size() const {return (_length);};
		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / (sizeof(node)));
		};
//			Element access:
		reference front() {return _init_node->next->_data;};
		const_reference front() const {return _init_node->next->_data;};
		reference back() {return _init_node->prev->_data;};
		const_reference back() const {return _init_node->prev->_data;};
//			Modifiers:
//			range (1)
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
			   typename enable_if<is_input_iterator<InputIterator>::value>::type* = 0) {
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
			_node_pointer tmp = CreateNode(val);
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
			_node_alloc.destroy(tmp);
			_node_alloc.deallocate(tmp, 1);
			_length -= 1;
		};
		void push_front (const value_type& val){
			_node_pointer tmp = CreateNode(val);
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
			_node_alloc.destroy(tmp);
			_node_alloc.deallocate(tmp, 1);
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
		void insert (iterator position, InputIterator first, InputIterator last,
			typename enable_if<is_input_iterator<InputIterator>::value>::type* = 0){
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
			if (*this == x)
				return;
			allocator_type swap_alloc = x._alloc;
			node_alloc swap_node_alloc = x._node_alloc;
			list_node<T>* swap_node_list = x._init_node;

			x._alloc = this->_alloc;
			x._node_alloc = this->_node_alloc;
			x._init_node = this->_init_node;

			this->_alloc = swap_alloc;
			this->_node_alloc = swap_node_alloc;
			this->_init_node = swap_node_list;

			ft::swap(_length, x._length);
		};
		void resize (size_type n, value_type val = value_type()){
			while (n > _length)
				push_back(val);
			while (n < _length)
				pop_back();
		};
//		entire list (1)
		void splice (iterator position, list& x) {
			splice(position, x, x.begin(), x.end());
		};
//		single element (2)
		void splice (iterator position, list& x, iterator i) {
			iterator next(i);
			++next;
			splice(position, x, i, next);
		};
//		element range (3)
		void splice (iterator position, list& x, iterator first, iterator last) {
			if (first == last)
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
				if (comp(*x_it, *m_it)) {
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
		template <class Compare>
		void sort (Compare comp) {
			if (empty())
				return ;

			iterator prev = begin();
			iterator next = ++begin();

			bool swapped = true;
			while (swapped)
			{
				swapped = false;
				while (next != end())
				{
					if (comp(*next, *prev))
					{
						splice(prev, *this, next);
						ft::swap(prev, next);
						swapped = true;
					}
					++prev;
					++next;
				}
				prev = begin();
				next = ++begin();
			}
		}
		void reverse() {
			if (empty())
				return;
			iterator finish = end();
			iterator start = begin();
			iterator next = ++begin();
			while (next != finish) {
				while (next != finish) {
					splice(start, *this, next);
					ft::swap(start, next);
					++start;
					++next;
				}
				--finish;
				start = begin();
				next = ++begin();
			}
		}
	};
//	relational operators
	template <class T> bool operator== (const list<T>& lhs, const list<T>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (typename list<T>::const_iterator l_it = lhs.begin(), r_it = rhs.begin(); l_it != lhs.end(); ++l_it,
				++r_it){
			if (!(*l_it == *r_it))
				return false;
		}
		return true;
	}
	template <class T> bool operator!= (const list<T>& lhs, const list<T>& rhs){
		return !(lhs == rhs);
	}
	template <class T> bool operator<  (const list<T>& lhs, const list<T>& rhs){
		typename list<T>::const_iterator l_it = lhs.begin(), r_it = rhs.begin();
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
