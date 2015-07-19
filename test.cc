#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>




std::vector <int> convert(std::string pos) {
	std::stringstream ss(pos);
	char c;
	int n;
	std::vector <int> result;
	ss >> c >> n;
	result.push_back(8 - n);
	result.push_back(c - 'a');
	return result;
}


int main (){
	std::string s;
	std::cin >> s;
	std::cout << convert(s)[0] << " " << convert(s)[1] << " " << std::endl;
}
