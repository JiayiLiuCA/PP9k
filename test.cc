#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <utility>





int main (){
	std::vector < std::pair<int, int> > tmp;
	std::pair <int, int> tmp2;
	
	tmp.push_back(tmp2);
	tmp2.first = 2;
	tmp2.second = 3;
	tmp.push_back(tmp2);
	for(int i = 0; i < tmp.size(); i ++) {
	std::cout << tmp[i].first << " " << tmp[i].second << " " << std::endl;
	}
}
