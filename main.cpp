#include <iostream>
#include "./src/list/list.hpp"
//DELETE
#include <list>
#include <string>
int main()
{
	std::list<int> int_list_std;
	std::list<int>::iterator it_std = int_list_std.begin();
	std::list<int>::iterator it_std_end = int_list_std.end();

	if (it_std == it_std_end)
		return 0;
	for (int i = 0;i < 5; i++)
	{
		int_list_std.push_back(i+1);
		++it_std;
		std::cout<<*it_std<<std::endl;
	}


	std::cout<<std::string(10, ' ')<<"My list"<<std::endl;
	ft::list<int> list_int_my;
	ft::list<int>::iterator it_my = list_int_my.;
	for (int i = 0; i < 5; i++)
	{

	}
	return 0;
}
