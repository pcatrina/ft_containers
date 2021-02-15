#ifndef FT_CONTAINERS_LIST_NODE_HPP
#define FT_CONTAINERS_LIST_NODE_HPP

template<typename T> struct list_node {
public:
	list_node		*prev;
	list_node		*next;
	T				data;

	list_node() : prev(nullptr), next(nullptr) {}
	list_node(T &data) : prev(nullptr), next(nullptr) {this->data = data;}
	list_node(T &data, list_node *prev, list_node *next)
		: prev(prev), next(next), data(data) {}
};

#endif //FT_CONTAINERS_LIST_NODE_HPP
