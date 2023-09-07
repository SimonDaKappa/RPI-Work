#include <iostream>
#include <list>

int main() {
	std::list<int> list1	= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::list<int>::iterator itr = list1.begin();
	while (itr != list1.end()) {
		
		std::list<int>::iterator itr2 = list1.begin();
		while (itr2 != list1.end()) {
			std::cout << *itr2 << ' ';
			itr2++;
		}
		std::cout << '\n';

		if (*itr == 5) {
			itr = list1.erase(itr);
		}
		itr++;
	}
}