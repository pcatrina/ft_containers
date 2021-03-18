#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include "map_node.hpp"
#include <limits>
#include <cstddef>


namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef ft::less<key_type> key_compare;
		typedef ft::less<value_type> value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef map_iterator<value_type, key_compare> iterator;
		typedef map_iterator<const value_type, key_compare> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		typedef map_node<typename ft::remove_const<value_type>::type> node;

	private:
		typedef typename allocator_type::template
		rebind<value_type>::other node_alloc;
		typedef typename node_alloc::pointer _node_pointer;
		allocator_type _alloc;
		key_compare _comp;
		value_compare _val_comp;
		size_type _length;


		node_alloc _node_alloc;
		_node_pointer _map_init;
		size_type _capacity;
	public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _comp(comp) {
		};
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type&
		alloc = allocator_type(), typename enable_if<is_input_iterator<InputIterator>::value>::type* = NULL) {
			_map_init = _node_alloc.allocate(1);
			_node_alloc.construct(_map_init, value_type());


		};
		map (const map& x): _alloc(x._alloc), _comp(x._comp), _length(x._length) {

		};
		~map() {};

//		Iterators
		iterator begin() {
			return ++iterator(_map_init);
		};

		mapped_type& operator[] (const key_type& k) {
		};

//		Modifiers
		pair<iterator,bool> insert (const value_type& val) {

		};

	};
		template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

		template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

		template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

		template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

		template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

		template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }
}

#endif //FT_CONTAINERS_MAP_HPP
