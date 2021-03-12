#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include <cstddef>
#include "../list/list_node.hpp"
#include "utils.hpp"

namespace ft {

//		Iterator for list - for more information read std::iterator
//		type: std::bidirectional_iterator_tag

//List Iterator
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
		friend class list;

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

//		Iterator for vector - for more information read std::iterator
//		type: std::random_access_iterator

//	Vector Iterator
	template<class T> class random_access_iterator {
	public:
		//		All possible member_types
		typedef T				value_type;
		typedef std::ptrdiff_t	difference_type;
		typedef T*				pointer;
		typedef T&				reference;
		typedef ft::random_access_iterator_tag	iterator_category;

//		You need to add list_node and list_iterator as a friend for
//		a logical comparison operator
		template<class > friend class vector;
		template<class > friend class random_access_iterator;
	private:
		value_type* _p;
	public:
		random_access_iterator() : _p(NULL) {}
		random_access_iterator(const random_access_iterator<value_type> &other) : _p(other._p) {}
		template<class U> random_access_iterator(random_access_iterator<U> const& other, typename
		ft::if_enable<!ft::is_const<U>::value>::type* = nullptr) : _p(other._p) {}
		random_access_iterator(value_type *p) : _p(p) {}
		~random_access_iterator() {}

		const random_access_iterator &operator=(const random_access_iterator &other) {_p=other._p; return *this;}
		reference operator*() const {return *_p;}
		pointer operator->() const {return _p;}

		template<typename U>
		friend bool operator==(const random_access_iterator<U> &lhs, const random_access_iterator<U> &rhs) {
			return lhs._p == rhs._p;
		}
		template<typename U>
		friend bool operator<(const random_access_iterator<U> &lhs, const random_access_iterator<U> &rhs) {
			return lhs._p < rhs._p;
		}
		random_access_iterator& operator++() {++_p; return *this;} //prefix inc
		random_access_iterator& operator++(int) { //postfix inc
			random_access_iterator tmp = *this;
			++(*this);
			return tmp;
		}
		random_access_iterator& operator--(){--_p; return *this;} //prefix dec
		random_access_iterator& operator--(int) { //postfix dec
			random_access_iterator tmp = *this;
			--(*this);
			return tmp;
		}
		random_access_iterator& operator+=(difference_type n) {_p += n; return *this;}
		random_access_iterator& operator+ (difference_type n) const {
			random_access_iterator tmp;
			*this += n;
			return tmp;
		}
		random_access_iterator& operator-=(difference_type n) {_p -= n; return *this;}
		random_access_iterator& operator- (difference_type n) {
			random_access_iterator tmp;
			*this -= n;
			return tmp;
		}
		reference operator[](difference_type n) const {return *(*this+n);}
	};
	template <class U>
	typename random_access_iterator<U>::difference_type operator- (random_access_iterator<U> &a, random_access_iterator<U>&b){
		return a - b;
	}
	template <class U>
	random_access_iterator<U> operator+ (typename random_access_iterator<U>::difference_type n,const random_access_iterator<U> & a) {
		return a + n;
	}
	template<class U>
	bool operator!=(const random_access_iterator<U> &lhs, const random_access_iterator<U> &rhs) {
		return !(lhs == rhs);
	}
	template<class U>
	bool operator>(const random_access_iterator<U> &lhs, const random_access_iterator<U> &rhs) {
		return lhs<rhs;
	}
	template<class U>
	bool operator<=(const random_access_iterator<U> &lhs, const random_access_iterator<U> &rhs) {
		return !(lhs<rhs);
	}
	template<class U>
	bool operator>=(const random_access_iterator<U> &lhs, const random_access_iterator<U> &rhs) {
		return !(lhs>rhs);
	}
}

#endif //FT_CONTAINERS_ITERATORS_HPP
