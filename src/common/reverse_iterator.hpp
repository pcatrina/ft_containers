#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include <cstddef>
#include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

namespace ft {
	template <class Iterator> class reverse_iterator {
	public:
		typedef Iterator								iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	private:
		iterator_type _it_type;
	public:
		reverse_iterator() : _it_type() {}
		explicit reverse_iterator(iterator_type it) : _it_type(it) {}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) {_it_type = rev_it._it_type;}

		iterator_type base() const {return _it_type;}
		reference operator*() const {iterator_type  tmp = _it_type; return *--tmp;}
		reverse_iterator operator+ (difference_type n) const {return reverse_iterator(_it_type - n);}
		reverse_iterator& operator++() {--_it_type; return *this;};
		reverse_iterator  operator++(int) {
			reverse_iterator temp = *this;
			++(*this);
			return temp;
		}
		reverse_iterator& operator+= (difference_type n) {_it_type += n; return *this;}
		reverse_iterator operator- (difference_type n) const {return reverse_iterator(_it_type + n);}
		reverse_iterator& operator--() {++_it_type; return *this;}
		reverse_iterator  operator--(int) {
			reverse_iterator temp = *this;
			--(*this);
			return temp;
		}
		reverse_iterator& operator-= (difference_type n) {_it_type -= n; return *this;}
		pointer operator->() const {return &(operator*());}
		reference operator[] (difference_type n) const {return *(*this + n);}
	};
//	(1)
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}
//	(2)
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.base() != rhs.base();
	}
//	(3)
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}
//	(4)
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	}
//	(5)
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}
//	(6)
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP
