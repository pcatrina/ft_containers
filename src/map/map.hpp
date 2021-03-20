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
		value_compare 	_val_comp;
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

		void DeleteNode(node* x) {
			_alloc.destroy(x);
			_alloc.deallocate(x, 1);
		}

//		CreateInit
		pointer CreatInit(){
			node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type());
			new_node->_parent = NULL;
			new_node->_left = NULL;
			new_node->_right = NULL;
			new_node->_height = 0;
			return (new_node);
		}
//		BTR_functions
//		ADD
		node* ADD(node* _cur, node* new_node) {
			if (_val_comp(new_node->_data, _cur->_data)) {
				if (_cur->_left)
					new_node = ADD(_cur->_left, new_node);
				else {
					new_node->_parent = _cur;
					_cur->_left = new_node;
				}
			} else if (_val_comp(_cur->_data, new_node->_data)) {
				if (_cur->_right)
					new_node = ADD(_cur->_right, new_node);
				else {
					new_node->_parent = _cur;
					_cur->_right = new_node;
				}
			} else
				return _cur;
			BALANCE(_cur);
			return new_node;
		}
//		ft::pair<node*, bool> DELETING(node *n, const key_type& k) {
//			ft::pair<node*, bool> ret (NULL, false);
//			if (!n)
//				return ret;
//			if (k < n->_data.first) {
//				ret = DELETING(n->_left, k);
//				n->_left = ret.first;
//			} else if (n->_data.first < k) {
//				ret = DELETING(n->_right, k);
//				n->_right = ret.first;
//			} else if ((n->_left == NULL) || (n->_right == NULL)) {
//				node* tmp = NULL;
//				if (n->_left)
//					tmp = tmp->_left;
//				else if (n->_right)
//					tmp = tmp->_right;
//				if (tmp) {
//					tmp->_parent = n->_parent;
//					if (tmp->_parent) {
//						if (tmp->_parent->_left == n)
//							tmp->_parent->_left = tmp;
//						else
//							tmp->_parent->_right = tmp;
//					}
//				}
//				DeleteNode(n);
//				n = tmp;
//				ret.second = true;
//			} else {
//				node *next = n->_right;
//				while (next->_left)
//					next = next->_left;
//			}
//		}
		node* BALANCE(node* _cur) {
			OVER_HEAD(_cur);
			if (BF(_cur) == 2) {
				if (BF(_cur->_right)<0)
					_cur->_right = RIGHT_SR(_cur->_right);
				return LEFT_SR(_cur);
			}
			if (BF(_cur) == -2) {
				if (BF(_cur->_left)>0)
					_cur->_left = LEFT_SR(_cur->_left);
				return RIGHT_SR(_cur);
			}
			return _cur;
		}

		int BF (node *_cur) {
			int h_left = 0;
			int h_right = 0;
			h_left = (_cur->_left ? _cur->_left->_height : 0);
			h_right = (_cur->_right ? _cur->_right->_height : 0);
			return ((h_right) - (h_left));
		};

		void OVER_HEAD(node *_cur) {
			int h_left = 0;
			int h_right = 0;
			if (_cur->_left)
				h_left = _cur->_left->_height;
			if (_cur->_right)
				h_right = _cur->_right->_height;
			_cur->_height = ((h_left>h_right) ? h_left : h_right) + 1;
		}

		node* RIGHT_SR(node *r) {
			node* l = r->_left;
			node* r2 = l->_right;
			l->_right = r;
			l->_parent = r->_parent;
			if (l->_parent) {
				if (l->_parent->_left == r)
					l->_parent->_left = l;
				else
					l->_parent->_right = l;
			}
			r->_left = r2;
			if (r2)
				r2->_parent = r;
			r->_parent = l;
			OVER_HEAD(r);
			OVER_HEAD(l);
			return l;
		}

		node* LEFT_SR(node *l) {
			node* r = l->_right;
			node* l2 = r->_left;
			r->_left = l;
			r->_parent = l->_parent;
			if (r->_parent) {
				if (r->_parent->_left == l)
					r->_parent->_left = r;
				else
					r->_parent->_right = r;
			}
			l->_right = l2;
			if (l2)
				l2->_parent = l;
			l->_parent = r;
			OVER_HEAD(l);
			OVER_HEAD(r);
			return r;
		}

		node * FIND_INIT(node* _cur) {
			while (_cur->_parent)
				_cur = _cur->_parent;
			return (_cur);
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

		void UnlinkTree() const {
			if (_init_node) {
				_start_node->_parent->_left = NULL;
				_end_node->_parent->_right = NULL;
				_start_node->_parent = _end_node;
				_end_node->_parent = _start_node;
			}
		}

		node* AddNewNode(node* _cur, node* new_node) {
			UnlinkTree();
			if (!_init_node)
				_init_node = new_node;
			else {
				new_node = ADD(_cur, new_node);
				_init_node = FIND_INIT(_init_node);
			}
			LinkDefaultTree();
			return new_node;
		}
		bool DeletingNode(key_type k) {
			UnlinkTree();
//			ft::pair<node *, bool> res;
//			res = DELETING(_init_node, k);
			node* finish = ___DELETE___(_init_node, k);
			_init_node = finish;
			LinkDefaultTree();
//			return res.second;
			return true;
		}

		node * ___DELETE___(node* x, const key_type &k) {
			if (!x)
				return NULL;
			if (k < x->_data.first) {
				x->_left = ___DELETE___(x->_left, k);
			} else if (x->_data.first < k) {
				x->_right = ___DELETE___(x->_right, k);
			} else {
				node* parent = x->_parent;
				node* l = x->_left;
				node* r = x->_right;
				DeleteNode(x);
				if (!r) return l;
				node* min = SearchMin(r);
				l->_parent = min;
				min->_left = r;
				min->_right = l;
				min->_parent = parent;
				return BALANCE(min);
			}
			return BALANCE(x);
		};

		node *SearchMin(node *x)
		{
			if (x->_left) return SearchMin(x->_left);
			else return x;
		}
		node *DeleteMin(node *x)
		{
			if (x->_left==0) return x->_right;
			x->_left=DeleteMin(x->_left);
			return BALANCE(x);
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
		iterator begin() { return ++iterator(_start_node);};
		const_iterator begin() const { return  ++const_iterator(_start_node);};

		iterator end() {return iterator (_end_node);};
		const_iterator end() const { return const_iterator(_end_node);};

		reverse_iterator rbegin() {return reverse_iterator(end());};
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());};

		reverse_iterator rend() {return reverse_iterator (begin());};
		const_reverse_iterator rend() const { return const_reverse_iterator (begin());};

//		Capacity:
		bool empty() const {return !(_length);};
		size_type size() const {return _length;};
		size_type max_size() const {return std::numeric_limits<size_type>::max() / (sizeof(node));};

//		Element access:
		mapped_type& operator[] (const key_type& k) {
			value_type val(k, mapped_type());
			iterator it = insert(val).first;
			return (*it).second;
		};

//		Modifiers
		ft::pair<iterator,bool> insert (const value_type& val) {
			node* new_node = CreateNode(val);
			node* tmp = AddNewNode(_init_node, new_node);
			if (tmp != new_node)
			{
				_alloc.destroy(new_node);
				_alloc.deallocate(new_node, 1);
				return ft::pair<iterator,bool>(tmp, false);
			}
			++_length;
			return ft::pair<iterator,bool>(iterator(new_node), true);
		}
		iterator insert (iterator position, const value_type& val) {
			if (position._data != _start_node && position._data != _end_node &&
					((_val_comp(val, position.next_node()->_data) && _val_comp(position.prev_node()->_data, val)))) {
				insert(val);
			} else {
				insert(val).first;
			}
		};
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
			   typename enable_if<is_input_iterator<InputIterator>::value>::type* = NULL) {
			while (first != last) {
				insert(*first);
				++first;
			}
		};
		void erase (iterator position) {

		};
		size_type erase (const key_type& k) {
			if (DeletingNode(k)) {
				--_length;
				return (1);
			} else
				return 0;
		};
		void erase (iterator first, iterator last) {

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
