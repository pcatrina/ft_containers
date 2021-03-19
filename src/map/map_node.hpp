#ifndef FT_CONTAINERS_MAP_NODE_HPP
#define FT_CONTAINERS_MAP_NODE_HPP

namespace ft {
	template<class Pair,
			class Alloc = std::allocator<Pair> > class map_node {
	public:
		typedef Pair value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
	private:
		typedef typename allocator_type::template
		rebind<value_type>::other pair_alloc;
		typedef typename pair_alloc::pointer _pair_pointer;
		allocator_type 	_alloc;
		_pair_pointer	_pair_init;
	public:
		map_node*		_parent;
		map_node*		_right;
		map_node*		_left;
		int 			_height;
		value_type		_data;
	public:
		map_node(): _parent(NULL), _right(NULL), _left(NULL), _height(1), _data() {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		};
		map_node(const value_type &data): _parent(NULL), _right(NULL), _left(NULL), _height(1), _data(data) {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		};
		map_node(const map_node &other)
		:_alloc(other._alloc), _pair_init(other._pair_init), _parent(other._parent),
		_right(other._right), _left(other._left), _height(other._height), _data(other._data) {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		};
		~map_node() {
			_alloc.destroy(_pair_init);
			_alloc.deallocate(_pair_init, 1);
		};

		const map_node&operator=(const map_node &rhs) {
			if (*this == *rhs)
				return (*this);
			_alloc = rhs._alloc;
			_pair_init = rhs._pair_init;
			_parent = rhs._parent;
			_right = rhs._right;
			_left = rhs._left;
			_height = rhs._height;
			_data = rhs._data;
			return (*this);
		};
	};
}

#endif //FT_CONTAINERS_MAP_NODE_HPP
