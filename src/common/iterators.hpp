#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include <cstddef>
#include <limits>
#include "../list/list_node.hpp"
#include "../map/map_node.hpp"
#include "utils.hpp"

namespace ft {

//		Iterator for list - for more information read std::iterator
//		type: std::bidirectional_iterator_tag

//List Iterator
	template<class T> class bidirectional_iterator {
	public:
//		All possible member_types
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef list_node<typename ft::remove_const<value_type>::type> node;

//		You need to add list_node and bidirectional_iterator as a friend for
//		a logical comparison operator
		template<class , class Alloc>
		friend class list;

		template<class >
		friend class bidirectional_iterator;

	private:
		node*		_p;
	public:
		bidirectional_iterator() : _p(nullptr) {}
		bidirectional_iterator(const bidirectional_iterator<value_type> &other) : _p(other._p) {}
		bidirectional_iterator(node *p) : _p(p) {}
		template <class U>
		bidirectional_iterator(bidirectional_iterator<U> const& other, typename ft::enable_if<!ft::is_const<U>::value>::type* = nullptr)
		: _p(other._p) {}
		~bidirectional_iterator() {}

		const bidirectional_iterator &operator=(const bidirectional_iterator &other) {_p=other._p; return *this;}
		reference operator*() const {return _p->_data;}
		pointer operator->() const {return &_p->_data;}

		template<typename U>
		friend bool operator==(const bidirectional_iterator<U> &lhs, const bidirectional_iterator<U> &rhs) {
			return lhs._p == rhs._p;
		}

		bidirectional_iterator& operator++() {_p = _p->next; return *this;};
		bidirectional_iterator  operator++(int) {
			bidirectional_iterator temp = *this;
			++(*this);
			return temp;
		}

		bidirectional_iterator& operator--() {_p = _p->prev; return *this;};
		bidirectional_iterator  operator--(int) {
			bidirectional_iterator temp = *this;
			--(*this);
			return temp;
		}
	};
	template<typename U> bool operator!=(const bidirectional_iterator<U> &lhs, const bidirectional_iterator<U> &rhs) {
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

//		You need to add list_node and bidirectional_iterator as a friend for
//		a logical comparison operator
		template < class , class Alloc> friend class vector;
		template<class > friend class random_access_iterator;
	private:
		value_type* _p;
	public:
		random_access_iterator() : _p(NULL) {}
		random_access_iterator(const random_access_iterator<value_type> &other) : _p(other._p) {}
		template<class U> random_access_iterator(random_access_iterator<U> const& other, typename
		ft::enable_if<!ft::is_const<U>::value>::type* = NULL) : _p(other._p) {}
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
			return *this;
		}
		random_access_iterator& operator--(){--_p; return *this;} //prefix dec
		random_access_iterator& operator--(int) { //postfix dec
			random_access_iterator tmp = *this;
			--(*this);
			return *this;
		}
		random_access_iterator& operator+=(difference_type n) {_p += n; return *this;}
		random_access_iterator operator+ (difference_type n) {
			random_access_iterator tmp(*this);
			tmp += n;
			return tmp;
		}
		random_access_iterator& operator-=(difference_type n) {_p -= n; return *this;}
		random_access_iterator operator- (difference_type n) {
			random_access_iterator tmp(*this);
			tmp -= n;
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

//		Iterator for map - for more information read std::iterator
//		type: std::random_access_iterator

//	Map iterator
	template<class T, class Compare = ft::less<typename T::first_type> > class map_iterator {
	public:
	//		All possible member_types
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::bidirectional_iterator_tag	iterator_category;
	typedef map_node<typename ft::remove_const<value_type>::type> node;
//		You need to add list_node and bidirectional_iterator as a friend for
//		a logical comparison operator
		template<class , class , class, class Alloc>
		friend class map;

		template<class, class >
		friend class map_iterator;
	private:
		node*	_data;
		Compare	_comp;

		node *next_node() {
			node* tmp = _data;
			if (tmp->_height == 0) {
				if (tmp->_parent->_right == tmp)
					return tmp;
				return tmp->_parent;
			} else if (tmp->_right) {
				tmp =  tmp->_right;
				while(tmp->_left)
					tmp = tmp->_left;
			} else {
				while (!_comp(this->_data->_data.first, tmp->_data.first))
					tmp = tmp->_parent;
			}
			return (tmp);
		}

		node *prev_node() {
			node *tmp = _data;
			if (tmp->_height == 0) {
				if (tmp->_parent->_left == tmp)
					return tmp;
				return tmp->_parent;
			} else if (tmp->_left) {
				tmp = tmp->_left;
				while (tmp->_right)
					tmp = tmp->_right;
			} else {
				while (!_comp(tmp->_data.first, this->_data->_data.first))
					tmp = tmp->_parent;
			}
			return (tmp);
		}

	public:
		map_iterator(): _data(NULL), _comp() {};
		map_iterator(const map_iterator &other): _data(other._data), _comp(other._comp) {};
		template<class U> map_iterator(map_iterator<U> *other,
		typename ft::enable_if<!ft::is_const<U>::value>::type* = NULL) {};
		map_iterator(node *data): _data(data), _comp() {};
		~map_iterator() {};

		const map_iterator&operator=(const map_iterator &other) {_data=other._data; _comp=other._comp; return *this;};
		reference operator*() const {return _data->_data;}
		pointer operator->() const {return &_data->_data;}

		template<class U> friend bool operator==(const map_iterator& lhs, const map_iterator& rhs) {
			return lhs._data == rhs._data;
		};

		map_iterator& operator++() {_data = next_node(); return *this;}
		map_iterator&operator++(int) {
			node tmp = *this;
			++(*this);
			return (tmp);
		}
		map_iterator& operator--() {_data = prev_node(); return *this;}
		map_iterator&operator--(int) {
			node tmp = *this;
			--(*this);
			return (tmp);
		}
	};
	template<class U> bool operator!=(const map_iterator<U> &lhs, const map_iterator<U> &rhs) {
		return !(lhs==rhs);
	}
}

#endif //FT_CONTAINERS_ITERATORS_HPP
