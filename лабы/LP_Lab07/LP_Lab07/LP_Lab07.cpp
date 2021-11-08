#include <iostream>
#include "Dictionary.h"
#include "stdafx.h"

using namespace Dictionary;
using namespace std;

void main()
{
	setlocale(LC_ALL, "rus");
	try
	{
		Instance d1 = Create( "Преподаватели", 5 );
		Entry e1 = { 1, "Первый" }, e2 = { 2,"два" },
			e3 = { 3,"три" }, e4 = { 4,"четыре" }, e5 = {5,"пять"};
		AddEntry(d1, e1);
		AddEntry(d1, e2);
		AddEntry(d1, e3);
		AddEntry(d1, e5);
		Entry ex2 = GetEntry(d1, 2);
		DelEntry(d1,2);
		Entry newentry1 = { 6,"six" };
		UpdEntry(d1,3,newentry1);
		Print(d1);


#if (defined(TEST_CREATE_01)+defined(TEST_CREATE_02)+defined(TEST_ADDENTRY_03)+defined(TEST_ADDENTRY_04)+defined(TEST_GETENTRY_05)+defined(TEST_GETENTRY_06)+defined(TEST_UPDENTRY_07)+defined(TEST_UPDENTRY_08)+defined(TEST_DICTIONARY))>1
#error Установка более одного макроса запрещена
#endif

#if defined(TEST_CREATE_01)
Instance d11 = Create("Преподаватели123456789", 5);
#endif


#if defined(TEST_CREATE_02)
Instance d22 = Create("Преподаватели", 105);

#endif


#if defined(TEST_ADDENTRY_03)
Instance d3 = Create("Преподаватели", 2);
Entry e33 = { 1, "Первый" }, e331 = { 2,"два" },
e332 = { 3,"три" }, e333 = { 4,"четыре" };
AddEntry(d3, e33);
AddEntry(d3, e331);
AddEntry(d3, e332);
AddEntry(d3, e333);
#endif

#if defined(TEST_ADDENTRY_04)
Instance d44 = Create("Преподаватели", 2);
Entry e44 = { 1, "Первый" }, e441 = { 1,"два" };
AddEntry(d44, e44);
AddEntry(d44, e441);
#endif

#if defined(TEST_GETENTRY_05)
Instance d1 = Create("Преподаватели", 5);
Entry e1 = { 1, "Первый" }, e2 = { 2,"два" },
e3 = { 3,"три" }, e4 = { 4,"четыре" }, e5 = { 5,"пять" };
AddEntry(d1, e1);
AddEntry(d1, e2);
AddEntry(d1, e3);
AddEntry(d1, e5);
Entry ex2 = GetEntry(d1, 4);
#endif

#if defined(TEST_GETENTRY_06)
Instance d4 = Create("Преподаватели", 5);
Entry e441 = { 1, "Первый" }, e442 = { 2,"два" },
e443 = { 3,"три" }, e444 = { 4,"четыре" }, e445 = { 5,"пять" };
AddEntry(d4, e441);
AddEntry(d4, e443);
AddEntry(d4, e445);
DelEntry(d4, 2);
#endif



#if defined(TEST_UPDENTRY_07)
Instance d21 = Create("Преподаватели", 5);
Entry e21 = { 1, "Первый" }, e22 = { 2,"два" },
e23 = { 3,"три" }, e24 = { 4,"четыре" }, e25 = { 5,"пять" };
AddEntry(d21, e21);
AddEntry(d21, e23);
AddEntry(d21, e24);
AddEntry(d21, e25);
UpdEntry(d21, 2, newentry1);
#endif


#if defined(TEST_DICTIONARY)
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
#endif 
	}
	catch (char* e)
	{
		cout << e << endl;
	}
}