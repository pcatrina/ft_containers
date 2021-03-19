#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include "map_node.hpp"
#include <limits>
#include <cstddef>


namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>,
			class Alloc = std::allocator<ft::map_node<ft::pair<const Key,T> > > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef ft::map_node<value_type> node_type;
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
		typedef ft::map_node<typename ft::remove_const<value_type>::type> node;

	private:
		typedef typename allocator_type::template
		rebind<value_type>::other node_alloc;
		typedef typename node_alloc::pointer _node_pointer;
		value_compare	_val_comp;
		allocator_type	_alloc;
		node_alloc _node_alloc;
		key_compare		_comp;
		node*		 	_init_node;
		node*			_start_node;
		node*			_end_node;
		size_type _length;
//		CreateNode
		pointer CreateNode(const value_type& data) {
			node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, data);
			return (new_node);
		}
//		CreateInit
		pointer CreatInit(){
			node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type());
			new_node->_parent = new_node;
			new_node->_left = new_node;
			new_node->_right = new_node;
			new_node->_height = 0;
			return (new_node);
		}
//		BTR_functions
//		ADD
		node* ADD(node* _init_node, node* new_node) {
			if (_val_comp(new_node->_data, _init_node->_data)) {
				if (_init_node->_left)
					new_node = ADD(_init_node->_left, new_node);
				else {
					new_node->_parent = _init_node;
					_init_node->_left = new_node;
				}
			} else if (_val_comp(_init_node->_data, new_node->_data)) {
				if (_init_node->_right)
					new_node = ADD(_init_node->_right, new_node);
				else {
					new_node->_parent = _init_node;
					_init_node->_right = new_node;
				}
			} else
				return _init_node;
			return new_node;
		}

		void LinkDefaultTree() const {
			if (!_init_node) {
				_start_node->_parent = _end_node;
				_end_node->_parent =_start_node;
			} else {
				node* tmp = _init_node;
				while (tmp->_left && (tmp->_left != _start_node))
					tmp = tmp->_left;
				_start_node->_parent = tmp;
				tmp->_left = _start_node;
				tmp = _init_node;
				while (tmp->_right && (tmp->_right != _end_node))
					tmp = tmp->_right;
				_end_node->_parent = tmp;
				tmp->_right = _end_node;
			}
		}

		node* AddNewNode(node* _init_node, node* new_node) {
			if (!_init_node)
				_init_node = new_node;
			else {
				new_node = ADD(_init_node, new_node);
//				_init_node = FIND_INIT();
			}
			LinkDefaultTree();
			return new_node;
		}

	public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _comp(comp), _init_node(NULL) {
			_start_node = CreatInit();
			_end_node = CreatInit();
			_length = 0;

			LinkDefaultTree();
		};
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type&
		alloc = allocator_type(), typename enable_if<is_input_iterator<InputIterator>::value>::type* = NULL):
			_alloc(alloc), _comp(_comp), _init_node(NULL) {
			_start_node = CreatInit();
			_end_node = CreatInit();
			_length = 0;

			LinkDefaultTree();
		};
		map (const map& x): _alloc(x._alloc), _comp(x._comp), _init_node(NULL) {
			_start_node = CreatInit();
			_end_node = CreatInit();
			_length = 0;

			LinkDefaultTree();
		};
		~map() {};

//		Iterators
		iterator begin() {
			return ++iterator(_start_node);
		};

		mapped_type& operator[] (const key_type& k) {
		};

//		Modifiers
		ft::pair<iterator,bool> insert (const value_type& val) {
			node* new_node = CreateNode(val);
			node* tmp = AddNewNode(_init_node, new_node);
			if (tmp != new_node)
			{
				delete new_node;
				return ft::pair<iterator,bool>(tmp, false);
			}
			++_length;
			return ft::pair<iterator,bool>(iterator(new_node), true);
		}

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
