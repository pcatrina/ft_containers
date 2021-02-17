#include <iostream>
#include "./src/list/list.hpp"
//DELETE
#include <list>
#include <string>
int main()
{
	std::list<char> int_list_std;
	std::list<char>::iterator it_std = int_list_std.begin();

	for (int i = 0;i < 26; i++)
	{
		int_list_std.push_back('A'+i);
		++it_std;
		std::cout<<*it_std;
	}
	std::list<char>::iterator it_std_end = int_list_std.end();
	--it_std_end;
	std::cout<<*it_std_end;
	++it_std_end;
	std::cout<<*it_std_end;
	++it_std_end;
	std::cout<<*it_std_end;

	std::cout<<std::endl;



	std::cout<<std::string(10, ' ')<<"My list"<<std::endl;
	ft::list<char> list_int_my;
	ft::list<char>::iterator my_it = list_int_my.begin();
	ft::list<char>::iterator my_it_end = list_int_my.end();

	for (int i = 0; i < 26; i++)
	{
		list_int_my.push_back('A'+ i);
		++my_it;
		std::cout<<*my_it;
	}
	std::cout<<std::endl;

	for (int i = 0; i < 26; i++)
	{
		--my_it_end;
		std::cout<<*my_it_end;
	}
	std::cout<<std::endl;
	list_int_my.push_front('Y');
	my_it = list_int_my.begin();
	std::cout<<*my_it<<std::endl;

	for (int i = 0; i < list_int_my.size(); i++)
	{
		std::cout<<*my_it;
		++my_it;
	}
	std::cout<<std::endl;
}