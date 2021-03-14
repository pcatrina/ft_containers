#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

namespace ft {
	template<class Key, class T, template<class U> class Allocator = allocator> class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef ft::less<key_type> key_compare;
//		value_compare	Nested function class to compare elements	see value_comp
		typedef bidirectional_iterator<value_type> iterator;
		typedef const bidirectional_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef const ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

	};

	template <class T, class U> struct pair {
	public:
		typedef T first_type;
		typedef U second_type;
	private:
		first_type first;
		second_type second;
	public:
		pair() :first(NULL), second(NULL) {};
		template<class U, class V> pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {};
		pair (const first_type& a, const second_type& b):first(a), second(b) {};
		pair& operator= (const pair& pr) {
			if (*this == pr)
				return (*this);
			*this = pr;
			return (*this);
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
	};
}

#endif //FT_CONTAINERS_MAP_HPP
