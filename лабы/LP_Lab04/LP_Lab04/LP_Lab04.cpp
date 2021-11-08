#include <limits.h>
#include <math.h>
#include <iostream>
using namespace std;
int n = 9;
auto X = 9 + n;
auto Y = 10 + n;
auto Z = 11 + n;
auto S = 1.0 + n;

int sum(int a, int b) { return a + b; }
int (*func) (int, int);
int main() {
	bool f1 = false, f2 = true;
	char lat = 's';
	wchar_t kir = L'ф';
	short x1 = X, x2 = -X;     //0012, ЕЕ                      //ffee
	short maxsh = 0x7fff, minsh = 0x8000 ;  //  SHRT_MIN
	unsigned short minush = 0x0, maxush = 0xffff;   //USHRT_MAX
	int y1 = Y, y2 = -Y;       //00000013, ED             //ffffffed
	int maxint = 0x7fffffff, minint = 0xcccccccc;
	unsigned int maxunin = 0xffffffff, minunin = 0x0;
	long z1 = Z, z2 = -Z;          //00000014, EF           //ffffffec  
	long maxlong = 0x7fffffff, minlong = 0x80000000;
	unsigned long maxunl = 0xffffffff, minunl = 0x0;
	float fl1 = S, fl2 = -S;  //0А.000 , F6.000



	float ff1 = 23.566f;
	float ff2 = 0;
    float inf = f1 / ff2;
	float inf1 = -f1 / ff2;
	float ind = inf*ff2;
	float ind1 = sqrt(-2);





	

	char c = 'a';                  
    wchar_t cat1 = L's';
    short cs1 = 0; 
	int ci1 = 5;
	float cf1 = 1.06f;
	double  cd1 = 13.56;


	char* ca = &c;                        char& caa = c;
	wchar_t* cat = &cat1;                 wchar_t& catt= cat1;
   short* cs = &cs1;                      short& css = cs1;
   int* ci=&ci1;                          int& cii = ci1;
   float* cf = &cf1;                      float& cff = cf1;
   double* cd = &cd1;                     double& cdd = cd1;

	cout << ca << '\t';                   cout  << caa << '\n';
    cout << cat << '\t';                  cout  << catt << '\n';
    cout  << cs << '\t';                  cout  << css << '\n';
    cout  << ci << '\t';                  cout  << cii << '\n';
    cout << cf << '\t';                   cout  << cff << '\n';
    cout  << cd << '\t';                  cout  << cdd << '\n';
	ca += 3; cat += 3; cs += 3; ci += 3; cf += 3; cd += 3;


	
	func = sum;
	int ss = func(1,2);
	cout << ss;
	

}
