#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <utility>





int main (){
	std::vector < int* > tmp;
	int n = 5;
	int *p = &n;
	int m = 4;
	int *q = &m;
	tmp.push_back(p);
	tmp.push_back(q);
	std::vector <int* > tmp2 = tmp;
	for(std::vector <int*>::iterator it = tmp.begin(); it != tmp.end(); it ++) {
		if(*it == p) tmp.erase(it);
	}
	for(std::vector <int*>::iterator it = tmp.begin(); it != tmp.end(); it ++) {
		std::cout << **it << std::endl;
	}
	for(std::vector <int*>::iterator it = tmp2.begin(); it != tmp2.end(); it ++) {
		std::cout << **it << std::endl;
	}

}
