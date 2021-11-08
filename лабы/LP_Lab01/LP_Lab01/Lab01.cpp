
/*������� 1*/
#include <iostream>
#include <conio.h>
using namespace std;
bool ifleap(int date);
bool correct(int date)
{
	bool correct=true;
	int amount[12] = { 31,28,31,30,31,30,31,31,30,31,30 };
	int day = date / 1000000;
	int month = (date / 10000) % 100;
	if ((date < 1000000)||(date>=100000000)) { cout << "������ ������� �� �������� �������" << endl; correct = false; }
	else
	{
		if ((((date % 1000000) / 10000) > 12) || (((date % 1000000) / 10000) < 1)) { cout << "����� ������ �������" << endl; correct = false; }
		bool ifl=ifleap(date);
		if ((ifl == true) && (month == 2) && (day > 28)) { cout << "���� ������ �������, ��� ����������" << endl; correct = false; }
		if (day > amount[month - 1]) { cout << "���� ������ �������, � ������ ������ ������ ����" << endl; correct = false; }
	}
	return correct;
}
int countDays(int date)
{                      
	int month, day, amount[12] = {31,28,31,30,31,30,31,31,30,31,30};
	month = (date / 10000) % 100;
	day = date / 1000000;
	for (int i = 0; i < 12; i++)
		if (month > (i + 1)) day += *(amount + i);
	if ((date % 4 == 0) && (month>2))  day++;
	cout << "��� " << day << " ���� � " << date % 10000 << " ����";
	return day;
}
bool ifleap(int date)
{
	bool ifl;
	if (date % 4 == 0) { cout << "��� ����������" << endl; ifl = true; }
	else {
		cout << "��� �� ����������" << endl; ifl = false;
	}
	return ifl;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int date;
	tryAgain:cout << "������� ���� � ������� ��������" << endl;
	cin >> date;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(2147483647, '\n');
		cout << "������ �����.������� ������ �����";
		goto tryAgain;

	}
	if (correct(date) == false) { cout << " ���������� ��� ���" << endl; goto tryAgain; }



	countDays(date);
	_getch();
}


