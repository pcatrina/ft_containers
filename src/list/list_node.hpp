#ifndef FT_CONTAINERS_LIST_NODE_HPP
#define FT_CONTAINERS_LIST_NODE_HPP

#include <limits>
#include <cstddef>
# include <sstream>
# include <typeinfo>
# include <iostream>

namespace ft {
	template<class T> class list_node {
	public:
		list_node *prev;
		list_node *next;
		T _data;
	public:
		list_node() : prev(nullptr), next(nullptr) {};
		list_node(T data) : prev(nullptr), next(nullptr), _data(data) {};
		list_node(T data, list_node *prev, list_node *next): prev(prev), next(next), _data(data) {};
		~list_node() {};

		const list_node &operator=(const list_node &rhs) {
			if (*this == rhs)
				return (*this);
			this->next = rhs.next;
			this->prev = rhs.prev;
			this->data = rhs.data;
			return (*this);
		};
	};
}

#endif //FT_CONTAINERS_LIST_NODE_HPP
