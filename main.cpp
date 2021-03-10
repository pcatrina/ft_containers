#include <iostream>
#include "./src/list/list.hpp"
int main()
{
	ft::list<int> ft_list;
	ft::list<int>::iterator ft_it;

	ft_it = ft_list.begin();

	for (size_t  i = 0; i < 10; i++)
	{
		ft_list.push_back(i);
		++ft_it;
		std::cout<<*ft_it;
	}
	std::cout<<std::endl;

	ft_it = ft_list.begin();
	++ft_it;
	++ft_it;
	++ft_it;
	ft_list.insert(ft_it, 9);

	ft_it = ft_list.begin();
	for (size_t  i = 0; i < ft_list.size(); i++)
	{
		std::cout<<*ft_it;
		++ft_it;
	}
	std::cout<<std::endl;

	ft_list.resize(5);

	ft_it = ft_list.begin();
	for (size_t  i = 0; i < ft_list.size(); i++)
	{
		std::cout<<*ft_it;
		++ft_it;
	}
	std::cout<<std::endl;

	ft_list.remove(9);
	ft_list.remove_if(ft::const_pred<int>(3));

	ft_it = ft_list.begin();
	for (size_t  i = 0; i < ft_list.size(); i++)
	{
		std::cout<<*ft_it;
		++ft_it;
	}
	std::cout<<std::endl;

	ft_list.push_back(2);
	ft_it = ft_list.begin();
	for (size_t  i = 0; i < ft_list.size(); i++)
	{
		std::cout<<*ft_it;
		++ft_it;
	}
	std::cout<<std::endl;

	ft_list.unique();
	ft_it = ft_list.begin();
	for (size_t  i = 0; i < ft_list.size(); i++)
	{
		std::cout<<*ft_it;
		++ft_it;
	}
	std::cout<<std::endl;
//	merge

	ft::list<int> sec_list;
	ft::list<int>::iterator sec_it;

	sec_it = sec_list.begin();

	for (size_t i = 1; i < 6; i++)
	{
		sec_list.push_back(i * 10);
		++sec_it;
		std::cout<<' '<<*sec_it;
	}
	std::cout<<std::endl;

	ft_list.sort();
	sec_list.sort();
	ft_list.merge(sec_list);

	ft_it = ft_list.begin();

	for (size_t  i = 0; i < ft_list.size(); i++)
	{
		std::cout<<' '<<*ft_it;
		++ft_it;
	}
	std::cout<<std::endl;

	std::cout<<sec_list.size()<<std::endl;

	ft_list.reverse();

	ft_it = ft_list.begin();

	for (size_t  i = 0; i < ft_list.size(); i++)
	{
		std::cout<<' '<<*ft_it;
		++ft_it;
	}
	std::cout<<std::endl;




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