#include <math.h>
#include <iostream>
using namespace std;

typedef unsigned char day;
typedef unsigned char month;
typedef unsigned int year;

struct Date
{
	day dd;
	month mm;
	year yyyy;
};

bool operator < (Date d1, Date d2)
{
  return ((d1.yyyy < d2.yyyy) || ((d1.yyyy == d2.yyyy) &&((d1.mm < d2.mm)|| ((d1.mm == d2.mm)&& (d1.dd < d2.dd)))));
}

bool operator > (Date d1, Date d2)
{
	return ((d1.yyyy > d2.yyyy) || ((d1.yyyy == d2.yyyy) && ((d1.mm > d2.mm) || ((d1.mm == d2.mm) && (d1.dd > d2.dd)))));
}

bool operator == (Date d1, Date d2)
{
	return ((d1.yyyy == d2.yyyy) && (d1.mm == d2.mm) && (d1.dd == d2.dd));
}


struct Dot
{
	int x; int y; int z;
};



float operator >> (Dot d1, Dot d2)
{
	float a = sqrt(pow(d2.x-d1.x,2)+ pow(d2.y-d1.y,2) + pow(d2.z-d1.z,2));
	return a;
}

Dot operator >= (Dot d1, Dot d2)
{
	Dot vv;
	vv.x = d2.x - d1.x;
	vv.y = d2.y - d1.y;
	vv.z = d2.z - d1.z;
	return vv;
}


int main()
{
	setlocale(LC_ALL, "Rus");

	Date date1 = { 7,1,1980 };
	Date date2 = { 7,2,1993 };
	Date date3 = { 7,1,1980 };

	if (date1 < date2) cout << "истина" << endl;
	else cout << "ложь" << endl;

	if (date1 > date2) cout << "истина" << endl;
	else cout << "ложь" << endl;

	if (date1 == date2) cout << "истина" << endl;
	else cout << "ложь" << endl;

	if (date1 == date3) cout << "истина" << endl;
	else cout << "ложь" << endl;

	cout << "----Задание 2----" << endl;

	Dot dot1 = { 12,34,56 };
	Dot dot2 = { 67,78,89 };

	printf("Расстояние между точками в пространстве равно %f\n", dot1>>dot2);

	Dot v1 = dot1 >= dot2;
	printf("Направляющий вектор через эти точки равен { %d, %d, %d }\n", v1.x, v1.y, v1.z);


	return 0;
}