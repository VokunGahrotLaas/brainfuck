#include <iostream>
#include <cstdint>
using namespace std;
int main(void) {
	uint8_t* p = new uint8_t[1024];
	for (size_t i = 0; i < 1024; ++i) p[i] = 0;
	*p += 8;
	while (*p != 0) {
		p += 1;
		*p += 8;
		p -= 1;
		*p -= 1;
	}
	p += 1;
	while (*p != 0) {
		p -= 1;
		*p += 4;
		p += 1;
		*p -= 1;
	}
	*p += 1;
	p -= 1;
	while (*p != 0) {
		p += 1;
		*p -= 1;
		p -= 1;
		while (*p != 0) {
			p += 1;
			*p += 4;
			p -= 1;
			*p -= 1;
		}
		p += 1;
		while (*p != 0) {
			p -= 1;
			*p += 8;
			p += 1;
			*p -= 1;
		}
		p -= 1;
		while (*p != 0) {
			p += 1;
			*p += 8;
			p -= 1;
			*p -= 1;
		}
		*p += 1;
		p += 1;
		while (*p != 0) {
			p += 1;
			*p += 10;
			while (*p != 0) {
				p += 1;
				*p += 5;
				p -= 1;
				*p -= 1;
			}
			p += 1;
			*p += 1;
			cout << static_cast<char>(*p);
			*p -= 1;
			cout << static_cast<char>(*p);
			while (*p != 0) {
				*p -= 1;
			}
			p -= 1;
			p -= 1;
			while (*p != 0) {
				*p -= 1;
			}
			p -= 1;
			*p -= 1;
			p += 1;
		}
		p -= 1;
		while (*p != 0) {
			p += 2;
			*p += 7;
			while (*p != 0) {
				p += 1;
				*p += 7;
				p -= 1;
				*p -= 1;
			}
			p += 1;
			cout << static_cast<char>(*p);
			*p += 5;
			cout << static_cast<char>(*p);
			while (*p != 0) {
				*p -= 1;
			}
			p -= 1;
			p -= 2;
			*p -= 1;
		}
	}
	p += 1;
	while (*p != 0) {
		p += 1;
		*p += 8;
		while (*p != 0) {
			p += 1;
			*p += 7;
			p -= 1;
			*p -= 1;
		}
		p += 1;
		cout << static_cast<char>(*p);
		while (*p != 0) {
			*p -= 1;
		}
		p -= 1;
		p -= 1;
		*p -= 1;
	}
	p -= 1;
	*p += 11;
	while (*p != 0) {
		p += 1;
		*p += 3;
		p += 1;
		*p += 9;
		p += 1;
		*p += 9;
		p += 1;
		*p += 1;
		p -= 4;
		*p -= 1;
	}
	p += 1;
	*p -= 1;
	cout << static_cast<char>(*p);
	p += 1;
	*p -= 1;
	cout << static_cast<char>(*p);
	*p += 7;
	cout << static_cast<char>(*p);
	*p += 11;
	cout << static_cast<char>(*p);
	p -= 1;
	cout << static_cast<char>(*p);
	p += 2;
	cout << static_cast<char>(*p);
	*p += 2;
	cout << static_cast<char>(*p);
	*p += 7;
	cout << static_cast<char>(*p);
	cout << static_cast<char>(*p);
	p -= 1;
	*p -= 1;
	cout << static_cast<char>(*p);
	p += 2;
	*p -= 1;
	cout << static_cast<char>(*p);
	while (*p != 0) {
		while (*p != 0) {
			*p -= 1;
		}
		p -= 1;
	}
}
