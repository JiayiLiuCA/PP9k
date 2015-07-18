#include <vector>
#include <iostream>
#include <algorithm>




int main () {
	std::vector<int> vec;
	vec.push_back(2);
	vec.push_back(3);
	vec.pop_back();
	std::cout << vec.size() << std::endl;
}
