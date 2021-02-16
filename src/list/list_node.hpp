#ifndef FT_CONTAINERS_LIST_NODE_HPP
#define FT_CONTAINERS_LIST_NODE_HPP

namespace ft
{
	template<class T>
	class list_node
	{
	public:
		list_node *prev;
		list_node *next;
		T data;
	public:
		list_node() : prev(nullptr), next(nullptr), data(0) {}
		list_node(T data) : prev(nullptr), next(nullptr), data(data) {}
		list_node(T data, list_node *prev, list_node *next)
				: prev(prev), next(next), data(data) {}
	};
}

#endif //FT_CONTAINERS_LIST_NODE_HPP
