#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include "../list/list.hpp"
#include <limits>
#include <cstddef>
# include <sstream>
# include <typeinfo>
# include <iostream>

namespace ft {
	template <class T, class Container = ft::list<T> > class stack {
	public:
		typedef T value_type;
 		typedef Container container_type;
		typedef std::size_t size_type;
	private:
		container_type _ctnr;
	public:
		explicit stack (const container_type& ctnr = container_type()): _ctnr(ctnr) {};
		bool empty() const {return _ctnr.empty();};
		size_type size() const {return _ctnr.size();};
		value_type& top() {return _ctnr.back();};
		const value_type& top() const { return _ctnr.back();};
		void push (const value_type& val) {_ctnr.push_back(val);};
		void pop() {_ctnr.pop_back();};
//		(1)
		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr == rhs._ctnr;
		};
//		(2)
		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return !(lhs == rhs);
		};
//		(3)
		friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr < rhs._ctnr;
		};
//		(4)
		friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr <= rhs._ctnr;
		};
//		(5)
		friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr > rhs._ctnr;
		};
//		(6)
		friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr >= rhs._ctnr;
		};
	};

}

#endif //FT_CONTAINERS_STACK_HPP
