#include <iostream>
#include <cstdint>
using namespace std;
int main(void) {
	uint8_t* p = new uint8_t[4];
	for (size_t i = 0; i < 4; ++i) p[i] = 0;
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
	cout << static_cast<char>(*p);
	p += 1;
	*p += 1;
	cout << static_cast<char>(*p);
	*p += 7;
	cout << static_cast<char>(*p);
	cout << static_cast<char>(*p);
	*p += 3;
	cout << static_cast<char>(*p);
	p += 1;
	*p += 2;
	cout << static_cast<char>(*p);
	p -= 2;
	*p += 15;
	cout << static_cast<char>(*p);
	p += 1;
	cout << static_cast<char>(*p);
	*p += 3;
	cout << static_cast<char>(*p);
	*p -= 6;
	cout << static_cast<char>(*p);
	*p -= 8;
	cout << static_cast<char>(*p);
	p += 1;
	*p += 1;
	cout << static_cast<char>(*p);
	p += 1;
	cout << static_cast<char>(*p);
}
