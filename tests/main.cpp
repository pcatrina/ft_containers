#include <iostream>
#include <map>
#include "../src/stack/stack.hpp"
#include "../src/vector/vector.hpp"
#include "../src/queue/queue.hpp"
#include "../src/deque/deque.hpp"
#include "../src/map/map.hpp"
#include "test.hpp"

int main() {
	std::cout<<std::string('*', 20)<<std::endl;
	while (true) {
		std::cout<<"***Insert index of test ---- :***"<<std::endl;
		std::cout<<"*** 1 - LIST"<<std::endl;
		std::cout<<"*** 2 - VECTOR"<<std::endl;
		std::cout<<"*** 3 - MAP"<<std::endl;
		std::cout<<"*** 4 - STACK"<<std::endl;
		std::cout<<"*** 5 - QUEUE"<<std::endl;
		int i = 0;
		std::cin >> i;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Wrong input , Try once more ..." << std::endl;
		}
		else if  (i > 0 && i <= 5)
		{
			if (i == 1)
				list_test();
			else if ( i == 2 )
				vector_test();
			else if ( i == 3 )
				map_test();
			else if (i == 4)
				stack_test();
			else
				queue_test();
		}
		else
			std::cout << "Wrong input , Try once more ..." << std::endl;
		std::cin.ignore(32767, '\n');
		system("clear");
		std::cout<<"*** Write MORE for more tests ***"<<std::endl;
		std::cout<<"*** Write EXIT for exit ***"<<std::endl;
		std::string res;
		std::cin>>res;
		if (res == "EXIT")
			break;
	}
	return 0;
}