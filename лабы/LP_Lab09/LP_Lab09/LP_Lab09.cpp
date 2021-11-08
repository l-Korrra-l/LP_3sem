#include "Varparm.h"
#include "Call.h"
#include <iostream>
using namespace std;
using namespace Varparm;
using namespace Call;

int defaultparm(int a, int a1, int a2, int a3, int a4, int b=1, int b1=2)
{
	return (a + a1 + a2 + a3 + a4 + b + b1) / 7;
};

void main()
{
	cout << "----ivarparm----" << endl;
	cout << ivarparm(0) << endl;
	cout << ivarparm(1, 1) << endl;
	cout << ivarparm(2, 1, 2) << endl;
	cout << ivarparm(6, 1, 2, 3, 4, 5, 6) << endl;

	cout << "----svarparm----" << endl;
	cout << svarparm(0) << endl;
	cout << svarparm(1, 1) << endl;
	cout << svarparm(2, 1, 2) << endl;
	cout << svarparm(6, 1, 2, 3, 4, 5, 6) << endl;

	cout << "----fvarparm----" << endl;
	cout << fvarparm(FLT_MAX) << endl;
	cout << fvarparm(1, FLT_MAX) << endl;
	cout << fvarparm(2.2, 1.1, FLT_MAX) << endl;
	cout << fvarparm(6.6, 1.4, 2.6, 3.6, 4.8, 5.0, FLT_MAX) << endl;

	cout << "----dvarparm----" << endl;
	cout << dvarparm(DBL_MAX) << endl;
	cout << dvarparm(1, DBL_MAX) << endl;
	cout << dvarparm(2.0, 1.0, DBL_MAX) << endl;
	cout << dvarparm(6.0, 1.0, 2.0, 3.0, 4.0, 5.0, DBL_MAX) << endl;

	int a = 1, b = 2, c = 3;
	cout << " _cdecl cdevl(a,b,c) = " << cdevl(a,b,c) << endl;
	cout << " _stdcall cstd(a, b, c) = " << cstd(a, b, c) << endl;
	cout << " _fastcall cfst((a, b, c) = " << cfst(a, b, c) << endl;

	defaultparm(1, 2, 3, 4, 5, 6);
}