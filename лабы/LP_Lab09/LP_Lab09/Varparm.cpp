#include "Varparm.h"
#include <limits.h>
#include <float.h>
#include <iostream>
namespace Varparm
{
	int ivarparm(int numb, ...)
	{
		if (numb > 0)
		{
			int* t = (int*)(&numb + 1);
			int temp = 1;
			for (int i = 0; i < numb; i++)
			{
				temp *= *(t + i);
			}
			return temp;
		}
		else return 0;
	};
	int svarparm(short numb, ...)
	{
		if (numb > 0)
		{
			short* t = (short*)(&numb + 2);
			short temp = 1;
			for (int i = 0; i < numb; i++)
			{
				temp *= t[i*2];
			}
			return (int)temp;
		}
		else return 0;
	};
	double fvarparm(float n, ... )
	{
		if (n != FLT_MAX)
		{
			double temp = 0;
			double* t = (double*)(&n + 1);
			short i = 0;
			while (t[i] != (double)FLT_MAX)
			{
				temp += t[i];
				i++;
			}

			return temp + (double)n;
		}
		else return 0;
	};
	double dvarparm(double n, ...)
	{
		if (n != DBL_MAX)
		{
			double temp = 0;
			double* t = &n+1;
			int i = 0;
			while (t[i]!=DBL_MAX)
			{

				temp += t[i];
				t++;
			}
			return temp;
		}
		else return 0;
	};
}