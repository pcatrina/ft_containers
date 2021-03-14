#ifndef FT_CONTAINERS_QUEUE_HPP
#define FT_CONTAINERS_QUEUE_HPP

#include "../list/list.hpp"
#include "../common/utils.hpp"
#include "../common/iterators.hpp"
#include "../common/reverse_iterator.hpp"
#include <limits>
#include <cstddef>

namespace ft
{
	template<class T, class Container = ft::list<T> > class queue
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef std::size_t size_type;
	private:
		container_type _cntr;
	public:
		explicit queue(const container_type &ctnr = container_type()) : _cntr(ctnr) {};

		bool empty() const { return _cntr.empty();};

		size_type size() const { return _cntr.size(); };

		value_type &front() { return _cntr.front(); };

		const value_type &front() const { return _cntr.front(); };

		value_type &back() { return _cntr.back(); };

		const value_type &back() const { return _cntr.back(); };

		void push(const value_type &val) { _cntr.push_back(val); };

		void pop() { _cntr.pop_back(); };
		//	(1)
		friend bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
			return (lhs._cntr == rhs._cntr);
		};
		//	(3)
		friend bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
			return (lhs._cntr < rhs._cntr);
		};
	};
//	(2)
	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs == rhs);
	};
//	(4)
	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs){
		return !(rhs < lhs);
	};
//	(5)
	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs <= rhs);
	};
//	(6)
	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs < rhs);
	};
}

#endif //FT_CONTAINERS_QUEUE_HPP
