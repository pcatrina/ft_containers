#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "../utils.hpp"
#include "list_node.hpp"

namespace ft {
	template < class T >
		class list {
		public:
			typedef T					value_type;
			typedef T& 					reference;
			typedef const T&			const_reference;
			typedef T*					pointer;
			typedef const T*			const_pointer;
			typedef std::ptrdiff_t 		difference_type;
			typedef std::size_t 				size_type;
//
		private:
			list_node<T>*	_before_node;
			list_node<T>*	_after_node;
			size_type		_length;

//			default (1)
			explicit list (const allocator_type& alloc = allocator_type()) : all_type(alloc) {
				last_node = all_node.allocate(1);
				all_node.constuct(last_node, list_node<T>());
				last_node->next = last_node;
				last_node->prev = last_node;
			}
//			fill (2)
			explicit list (size_type n, const value_type& val = value_type(),
						   const allocator_type& alloc = allocator_type()) {

			}
//			range (3)
			template <class InputIterator>
			list (InputIterator first, InputIterator last,
				  const allocator_type& alloc = allocator_type()) {

			}
//			copy (4)
			list (const list& x) {

			}


	};
}

#endif //FT_CONTAINERS_LIST_HPP
