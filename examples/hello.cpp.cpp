#include <iostream>
#include <cstdint>
using namespace std;
int main(void) {
	uint64_t* p = new uint64_t[1024];
	for (size_t i = 0; i < 1024; ++i) p[i] = 0;
	*p += 10;
	while (*p != 0) {
		p += 1;
		*p += 7;
		p += 1;
		*p += 10;
		p += 1;
		*p += 3;
		p += 1;
		*p += 1;
		p -= 4;
		*p -= 1;
	}
	p += 1;
	*p += 2;
	cout << *p;
	p += 1;
	*p += 1;
	cout << *p;
	*p += 7;
	cout << *p;
	cout << *p;
	*p += 3;
	cout << *p;
	p += 1;
	*p += 2;
	cout << *p;
	p -= 2;
	*p += 15;
	cout << *p;
	p += 1;
	cout << *p;
	*p += 3;
	cout << *p;
	*p -= 6;
	cout << *p;
	*p -= 8;
	cout << *p;
	p += 1;
	*p += 1;
	cout << *p;
	p += 1;
	cout << *p;
}
