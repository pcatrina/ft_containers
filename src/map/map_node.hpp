#ifndef FT_CONTAINERS_MAP_NODE_HPP
#define FT_CONTAINERS_MAP_NODE_HPP

namespace ft {
	template<class T> class map_node {
	public:
		map_node*		_parent;
		map_node*		_right;
		map_node*		_left;
		int 			_height;
		T				_data;
	public:
		map_node(): _parent(NULL), _right(NULL), _left(NULL), _data(NULL), _height(1) {};
		map_node(const T data): _parent(NULL), _right(NULL), _left(NULL), _data(data), _height(1) {};
		map_node(const map_node &other)
		: _parent(NULL), _right(NULL), _left(NULL), _data(NULL), _height(1) { *this ==other; };
		~map_node();

		const map_node&operator=(const map_node &rhs) {
			if (*this == *rhs)
				return (*this);
			_right = rhs._right;
			_left = rhs._left;
			_data = rhs._data;
			return (*this);
		};
	};
}

#endif //FT_CONTAINERS_MAP_NODE_HPP
