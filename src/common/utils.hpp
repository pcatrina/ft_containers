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

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> {typedef T type;};

	template <class T> struct is_type { typedef void type; };

	template <class InpIter>
	struct is_pointer {
		template <class T>
		static char is_ptr(T *);

		static double is_ptr(...);

		static InpIter t;
		enum { value = sizeof(is_ptr(t)) == sizeof(char) };

	};

	template <class Iter>
	struct is_iterator {
		template <class T>
		static char is_iter(typename ft::is_type<typename T::value_type>::type*,
							typename ft::is_type<typename T::difference_type>::type*,
							typename ft::is_type<typename T::pointer>::type*,
							typename ft::is_type<typename T::reference>::type*,
							typename ft::is_type<typename T::iterator_category>::type*);

		template <class>
		static double is_iter(...);

		enum { value = (sizeof(is_iter<Iter>(NULL, NULL, NULL, NULL, NULL)) == sizeof(char)
						|| is_pointer<Iter>::value)
		};
	};

	template <class InputIter>
	struct is_input_iterator
	{
		template <class T>
		static char is_input_iter(typename T::iterator_category*);

		template <class>
		static double is_input_iter(...);

		static ft::output_iterator_tag* output_iterator;

		enum { value = ((is_iterator<InputIter>::value
						 && !(sizeof(is_input_iter<InputIter>(output_iterator)) == sizeof(char))))
		};
	};

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
		const_pred() {};
	public:
		const_pred(const T& value) : _value(value) { }
		bool operator()(const T& x) { return _value == x; }
	};
	template <class T> class binary_pred {
	public:
		bool operator()(const T& val1, const T& val2) { return val1 == val2; }
	};

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 f_argument_type;
		typedef Arg2 s_argument_type;
		typedef Result r_type;
	};

	template <class T> struct greater : binary_function<T,T,bool> {
		bool operator() (const T&x, const T&y) const {return x>y;}
	};

	template <class T> struct less : binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x<y;}
	};

//	PAIR
	template <class T1, class T2> struct pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		first_type first;
		second_type second;
	public:
		pair() :first(), second() {};
		template<class U, class V> pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {};
		pair (const first_type& a, const second_type& b):first(a), second(b) {};
		pair& operator= (const pair& pr) {
			if (*this == pr)
				return (*this);
			*this = pr;
			return (*this);
		};
	};
}


#endif //FT_CONTAINERS_UTILS_HPP
