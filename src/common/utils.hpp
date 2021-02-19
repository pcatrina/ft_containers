#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

namespace ft {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<bool _bool, class T = void> struct if_enable {};
	template<class T> struct if_enable<true, T> 		{typedef T type; };

	template<class T> struct remove_const				{typedef T type;};
	template<class T> struct remove_const<const T>	{typedef T type;};

	template<class T> struct is_const					{enum {value = false};};
	template<class T> struct is_const<const T>		{enum {value = true};};

	template<class T> void swap(T &first, T &second){
		T tmp(first);
		first = second;
		second = tmp;
	};
//	Predicate class
	template <class T> class const_pred {
		const T _value;
		const_pred();
	public:
		const_pred(const T& value) : _value(value) { }
		bool operator()(const T& x) { return _value == x; }
	};
	template <class T> class binary_pred {
	public:
		bool operator()(const T& val1, const T& val2) { return val1 == val2; }
	};
}


#endif //FT_CONTAINERS_UTILS_HPP
