//MerhelCaroline2002
//04D 065 072 068 065 06C 043 061 072 06F 06C 069 06E 065 032 030 030 032
//4D 65 72 68 65 6C 43 61 72 6F 6C 6E 65 32 30 30 32
//004D 0065 0072 0068 0065 006C 0043 0061 0072 006F 006C 006E 0069 0065 0032 0030 0030 0032
//МергельКаролина2002
//41C 435 440 433 435 43B 44C 41A 430 440 43E 43B 438 43D 430 032 030 030 032
//D09C D0B5 D180 D0B3 D0B5 D0BB D18C D09A D0B0 D180 D0BE D0BB D0B8 D0BD D0B0 0032 0030 0030 0032
//041С 0435 0440 0433 0435 043B 044C 041A 0430 0440 043E 043B 0438 043D 0430 0032 0030 0030 0032
//Мергель2002Caroline
//41C 435 440 433 435 43B 44C 032 030 030 032 043 061 072 06F 06C 069 06E 065
//D09C D0B5 D180 D0B3 D0B5 D0BB D18C 32 30 30 32 43 61 72 6F 6C 6E 65 
//041С 0435 0440 0433 0435 043B 044C 0032 0030 0030 0032 0043 0061 0072 006F 006C 006E 0069 0065
#include <cstdlib>
#include <iostream>

char lf[] = "MerhelCaroline2002";
char rf[]= "МергельКаролина2002";
char lr[]= "Мергель2002Caroline";

wchar_t Llp[] = L"MerhelCaroline2002";
wchar_t Lrp[] = L"МергельКаролина2002";
wchar_t Llr[] = L"Мергель2002Caroline";


char* UpperW1251(char* destination, char* source)
{
	int size = strlen(source);
	for (int i = 0; i < size; i++)
	{
		if ((source[i] <= 'я') && (source[i] >= 'а')) destination[i] = source[i] + 'А'-'а';
		else if ((source[i] <= 'z')&&(source[i] >= 'a')) destination[i] = source[i] +'A'-'a';
		else destination[i] = source[i];
	}
	return destination;
}

int main()
{
	setlocale(LC_CTYPE,"Russian");
	char source[] = "Мергель2002Caroline";
	char destination[] = "1111111111111111111";
	UpperW1251(destination, source);
	std::cout << destination << std::endl;
	
	system("pause");
	return 0;
}