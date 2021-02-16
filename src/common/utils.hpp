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
}


#endif //FT_CONTAINERS_UTILS_HPP
