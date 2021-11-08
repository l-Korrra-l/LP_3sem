#include <iostream>
#pragma comment (lib, "..\\Debug\\LP_asm01a.lib")

extern "C"
{
	int __stdcall getmax(int*, int);
	int __stdcall getmin(int*, int);
}

int main()
{
	int mas[10] = { -3, 18, 27, -9, -17, 12, 83, -2, 10, 11 };
	int max = getmax(mas, sizeof(mas) / sizeof(int));
	int min = getmin(mas, sizeof(mas) / sizeof(int));
	std::cout << "getmax-getmin=" << max - min << std::endl;
	return 0;
}