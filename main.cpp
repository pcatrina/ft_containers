#include <iostream>
#include <map>
#include "./src/list/list.hpp"
#include "./src/stack/stack.hpp"
#include "./src/vector/vector.hpp"
#include "./src/queue/queue.hpp"
#include "./src/deque/deque.hpp"
#include "./src/map/map.hpp"
int main()
{
//	Today test

//ft::map<int, std::string> my_string;
//
//ft::map<int, std::string>::iterator it_ft;

ft::pair<int, std::string> my_pair(1, "A");
ft::pair<int, std::string> my_pair_1(2, "B");
ft::pair<int, std::string> my_pair_2(3, "C");


//
ft::map_node<ft::pair<int, std::string> > my_node(my_pair);
//
//ft::map_node<ft::pair<int, std::string> > my_sec_node(my_node);

ft::map<int, std::string> my_map;
//
my_map.insert(my_pair);
my_map.insert(my_pair_1);
my_map.insert(my_pair_2);
for (size_t i = 4; i <= 26 ; ++i) {
	my_map[i] = (static_cast<char>(64 + i));
}

ft::map<int, std::string>::iterator it;

it = my_map.begin();

std::cout<<it->second<<std::endl;

++it;

std::cout<<it->second<<std::endl;

it = --(my_map.end());

std::cout<<it->second<<std::endl;

ft::map<int, std::string>::iterator it_my;

it = my_map.begin();

std::string Title = " *** MY _ MAP *** ";

std::cout<<Title<<"\n";


for (size_t  i = 0; i != my_map.size() ; ++it, ++i) {
	std::cout<<" "<<it->first<<" - "<<it->second<<std::endl;
}

my_map.erase(16);

std::cout<<Title<<"\n";

it = my_map.begin();

for (size_t  i = 0; i != my_map.size() ; ++it, ++i) {
	std::cout<<" "<<it->first<<" - "<<it->second<<std::endl;
}

std::cout<<" *** STD *** "<<"\n";

std::pair<int, std::string> std_pair(1, "A");
std::pair<int, std::string> std_pair_1(2, "B");

std::map<int, std::string> std_map;
std_map.insert(std_pair);
std::map<int, std::string>::iterator std_it;
std_it = std_map.begin();
std::cout<<std_it->second<<std::endl;

std::cout<<" *** MAX_SIZE *** "<<"\n";
std::cout<<my_map.max_size()<<std::endl;
std::cout<<std_map.max_size()<<std::endl;

//	Deque

//	ft::deque<std::string> my_deque(5, "Hi");
//	for (size_t i = 0; i != my_deque.size(); ++i) {
//		std::cout<<' '<<my_deque[i];
//	}
//	std::cout<<'\n';
//	ft::deque<std::string> my_doub_deque(my_deque);
//
//	for (size_t i = 0; i != my_doub_deque.size(); ++i) {
//		std::cout<<' '<<my_doub_deque[i];
//	}
//	std::cout<<'\n';
//
//	ft::deque<std::string>::iterator d_it;
//
//	std::cout<<my_deque.max_size()<<'\n';

//
//	ft::vector<char> my_vec;
//	ft::vector<char> ft_vec(1, 'a');
//	ft::vector<char>::iterator ft_vec_it;
//	ft::vector<char>::iterator ft_vec_it_sec;
//
//	ft_vec.push_back('b');
//	ft_vec.push_back('c');
//	ft_vec.push_back('d');
//	ft_vec.push_back('e');
//
//	ft::vector<char> d_vec(ft_vec);
//	d_vec.clear();
//	ft_vec.push_back(48);
//
//	std::cout<<*ft_vec.begin()<<std::endl;
//	ft_vec.push_back('a');
//	std::cout<<ft_vec.size()<<std::endl;
//	for (size_t i = 0; i < ft_vec.size(); i++) {
//		std::cout<<' '<<ft_vec[i];
//	}
//	std::cout<<std::endl;
//
//	ft_vec.resize(15,'l');
//	for (size_t i = 0; i < ft_vec.size(); i++) {
//		std::cout<<' '<<ft_vec[i];
//	}
//	std::cout<<std::endl;
//
//	ft_vec.push_back('X');
//	ft_vec.pop_back();
//	ft_vec.push_back('Y');
//
//	for (size_t i = 0; i < ft_vec.size(); i++) {
//		std::cout<<' '<<ft_vec[i];
//	}
//	std::cout<<std::endl;
//
//	ft_vec.push_back('Z');
//	std::cout<<"size: "<<ft_vec.size()<<std::endl;
//	std::cout<<"capacity: "<<ft_vec.capacity()<<std::endl;
//	std::cout<<"max_size: "<<ft_vec.max_size()<<std::endl;
//	std::cout<<"empty: "<<ft_vec.empty()<<std::endl;
//
//	for(size_t i = 0; i<ft_vec.size(); i++)
//		ft_vec.at(i) = 'a' + i;
//
//	std::cout<< "my vector contains: ";
//	for (size_t i = 0; i<ft_vec.size(); i++)
//		std::cout<<' '<<ft_vec.at(i);
//	std::cout<<'\n';
//
//	std::cout<<"front: "<<ft_vec.front()<<std::endl;
//	std::cout<<"back: "<<ft_vec.back()<<std::endl;
//
//	ft_vec.insert(ft_vec.begin(), 1, 'T');
//	std::cout<< "my vector contains: ";
//	for (size_t i = 0; i<ft_vec.size(); i++)
//		std::cout<<' '<<ft_vec.at(i);
//	std::cout<<'\n';
//
//	ft_vec.erase(ft_vec.begin());
//	for (size_t i = 0; i < ft_vec.size(); i++) {
//		std::cout<<' '<<ft_vec[i];
//	}
//	std::cout<<std::endl;
//
//	for (size_t i = 0; i < d_vec.size(); i++) {
//		std::cout<<' '<<d_vec[i];
//	}
//	std::cout<<std::endl;
//
//	ft_vec.swap(d_vec);
//
//	for (size_t i = 0; i < d_vec.size(); i++) {
//		std::cout<<' '<<d_vec[i];
//	}
//	std::cout<<std::endl;
//
//	d_vec.swap(d_vec);
//	d_vec.swap(ft_vec);
//	for (size_t i = 0; i < d_vec.size(); i++) {
//		std::cout<<' '<<d_vec[i];
//	}
//	std::cout<<std::endl;
//
//	if (ft_vec < d_vec)
//		std::cout<<'Y'<<std::endl;
//	else
//		std::cout<<'N'<<std::endl;
//
//////	*** ft_stack ***
//
//ft::stack<int> first;
//ft::stack<int> second(first);
//ft::stack<int, ft::list<int> > third;
//
//ft::queue<int> my_queue;
//my_queue.push(10);
//my_queue.push(11);
//my_queue.push(12);
//my_queue.push(13);
//
//while (!my_queue.empty()) {
//	std::cout<<my_queue.back()<<std::endl;
//	my_queue.pop();
//}
//
//
//my_queue.push(10);

//	*** ft_list ***

//	ft::list<std::string> list_string(5, "Hi all");
//	ft::list<std::string>::iterator string_iterator;
//
//	string_iterator = list_string.begin();
//	for(;string_iterator != list_string.end(); ++string_iterator) {
//		std::cout<<' '<<*string_iterator;
//	}
//	std::cout<<'\n';
//
//	ft::list<char> char_list(5, 'A');
//	char_list.clear();
//
//
//	ft::list<int> ft_list;
//	ft::list<int>::iterator ft_it;
//
//	ft_it = ft_list.begin();
//
//	for (size_t  i = 0; i < 10; i++)
//	{
//		ft_list.push_back(i);
//		++ft_it;
//		std::cout<<*ft_it;
//	}
//	std::cout<<std::endl;
//
//	ft_it = ft_list.begin();
//	++ft_it;
//	++ft_it;
//	++ft_it;
//	ft_list.insert(ft_it, 9);
//
//	ft_it = ft_list.begin();
//	for (size_t  i = 0; i < ft_list.size(); i++)
//	{
//		std::cout<<*ft_it;
//		++ft_it;
//	}
//	std::cout<<std::endl;
//
//	ft_list.resize(5);
//
//	ft_it = ft_list.begin();
//	for (size_t  i = 0; i < ft_list.size(); i++)
//	{
//		std::cout<<*ft_it;
//		++ft_it;
//	}
//	std::cout<<std::endl;
//
//	ft_list.remove(9);
//	ft_list.remove_if(ft::const_pred<int>(3));
//
//	ft_it = ft_list.begin();
//	for (size_t  i = 0; i < ft_list.size(); i++)
//	{
//		std::cout<<*ft_it;
//		++ft_it;
//	}
//	std::cout<<std::endl;
//
//	ft_list.push_back(2);
//	ft_it = ft_list.begin();
//	for (size_t  i = 0; i < ft_list.size(); i++)
//	{
//		std::cout<<*ft_it;
//		++ft_it;
//	}
//	std::cout<<std::endl;
//
//	ft_list.unique();
//	ft_it = ft_list.begin();
//	for (size_t  i = 0; i < ft_list.size(); i++)
//	{
//		std::cout<<*ft_it;
//		++ft_it;
//	}
//	std::cout<<std::endl;
////	merge
//
//	ft::list<int> sec_list;
//	ft::list<int>::iterator sec_it;
//
//	sec_it = sec_list.begin();
//
//	for (size_t i = 1; i < 6; i++)
//	{
//		sec_list.push_back(i * 10);
//		++sec_it;
//		std::cout<<' '<<*sec_it;
//	}
//	std::cout<<std::endl;
//
//	ft_list.sort();
//	sec_list.sort();
//	ft_list.merge(sec_list);
//
//	ft_it = ft_list.begin();
//
//	for (size_t  i = 0; i < ft_list.size(); i++)
//	{
//		std::cout<<' '<<*ft_it;
//		++ft_it;
//	}
//	std::cout<<std::endl;
//
//	std::cout<<sec_list.size()<<std::endl;
//
//	ft_list.reverse();
//
//	ft_it = ft_list.begin();
//
//	for (size_t  i = 0; i < ft_list.size(); i++)
//	{
//		std::cout<<' '<<*ft_it;
//		++ft_it;
//	}
//	std::cout<<std::endl;


//	STD::LIST

//	std::cout<<std::string(10, ' ')<<"STD output"<<std::endl;
//
//	std::list<char> std_std_list;
//	std::list<char>::iterator std_std_it;
//	std_std_it = std_std_list.begin();
//	for(int i = 0; i < 26; i++)
//	{
//		std_std_list.push_back('A' + i);
//		++std_std_it;
//		std::cout<<*std_std_it;
//	}
//	std::cout<<std::endl;
//
//	std::list<char> ft_std_list;
//	std::list<char>::iterator ft_std_it;
//	ft_std_it = ft_std_list.begin();
//	for(int i = 0; i < 26; i++)
//	{
//		ft_std_list.push_back('a' + i);
//		++ft_std_it;
//		std::cout<<*ft_std_it;
//	}
//	std::cout<<std::endl;
//
//	for (size_t i = 0; i < ft_std_list.size() - 13; i++)
//		++ft_std_it;
//	std::cout<<*ft_std_it<<std::endl;
//
//	ft_std_list.splice(ft_std_it, std_std_list, std_std_list.begin(), std_std_list.end());
//
//	ft_std_it = ft_std_list.begin();
//	for (size_t i = 0; i < ft_std_list.size(); i++)
//	{
//		++ft_std_it;
//		std::cout<<*ft_std_it;
//	}
//	std::cout<<std::endl;

//	std::cout<<std::string(10, ' ')<<"unique test\n";
//ft::list<char> list;
//	for (int i = 0; i < 10; i++ )
//	{
//		list.push_back('a');
//	}
//	list.unique();
//	std::cout<<list.size()<<std::endl;
//
//	if (list < ft_list)
//	{
//		return 1;
//	}


	return 0;
}