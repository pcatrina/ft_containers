#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include <cstddef>
#include "../list/list_node.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"

//		Iterator for list - for more information read std::iterator
//		type: std::bidirectional_iterator_tag

namespace ft {
	template<class T>
	class list_iterator {
	public:
//		All possible member_types
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef list_node<typename ft::remove_const<T>::type>	node;

//		You need to add list_node and list_iterator as a friend for
//		a logical comparison operator
		template<class >
		friend class list_node;

		template<class >
		friend class list_iterator;

	private:
		node*		_p;
	public:
		list_iterator() : _p(nullptr) {}
		list_iterator(const list_iterator<value_type> &other) : _p(other._p) {}
		list_iterator(node *p) : _p(p) {}
		template <class U>
		list_iterator(list_iterator<U> const& other, typename ft::if_enable<!ft::is_const<U>::value>::type* = nullptr)
		: _p(other._p) {}
		~list_iterator() {}

		const list_iterator &operator=(const list_iterator &other) {_p=other._p; return *this;}
		reference operator*() const {return _p->data;}
		pointer operator->() const {return &_p->data;}

		template<typename U>
		friend bool operator==(const list_iterator<U> &lhs, const list_iterator<U> &rhs) {
			return lhs._p == rhs._p;
		}

		list_iterator& operator++() {_p = _p->next; return *this;};
		list_iterator  operator++(int) {
			list_iterator temp = *this;
			++(*this);
			return temp;
		}

		list_iterator& operator--() {_p = _p->prev; return *this;};
		list_iterator  operator--(int) {
			list_iterator temp = *this;
			--(*this);
			return temp;
		}
	};

	template<typename U>
	bool operator!=(const list_iterator<U> &lhs, const list_iterator<U> &rhs) {
		return !(lhs == rhs);
	}
}

#endif //FT_CONTAINERS_ITERATORS_HPP