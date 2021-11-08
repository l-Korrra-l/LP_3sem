#include <iostream>
#include "..\LP_Lab08L\Dictionary.h"

#pragma comment(lib,"C:\\Users\\User\\Documents\\ЯП\\LP_Lab08S\\Debug\\LP_Lab08L.lib")

using namespace Dictionary;
using namespace std;

void main()
{
	setlocale(LC_ALL, "rus");
	try
	{
		Instance d51 = Create("Преподаватели", 7);
		Entry e51 = { 1, "Первый" }, e52 = { 2,"два" },
			e53 = { 3,"три" }, e54 = { 4,"четыре" }, e55 = { 5,"пять" }, e56 = { 6,"six" }, e57 = { 7,"seven" };
		AddEntry(d51, e51);
		AddEntry(d51, e53);
		AddEntry(d51, e54);
		AddEntry(d51, e55);
		AddEntry(d51, e56);
		AddEntry(d51, e57);
		Print(d51);
		Instance d2 = Create("Студенты", 7);
		Entry s1 = { 1, "first" }, s2 = { 2,"sec" },
			s3 = { 3,"third" }, s4 = { 4,"444" }, s5 = { 5,"55" }, s6 = { 6,"616" }, s7 = { 7,"77n" };
		AddEntry(d2, s1);
		AddEntry(d2, s3);
		AddEntry(d2, s4);
		AddEntry(d2, s5);
		AddEntry(d2, s6);
		AddEntry(d2, s7);
		Print(d2);

	}
	catch (char* e)
	{
		cout << e << endl;
	}
}