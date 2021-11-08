#pragma once
#include <vector>
#include <string>
#define IN_MAX_LEN_TEXT 1024*1024	// ћаксимальный размер исходного кода = 1MB 
#define IN_CODE_ENDL '\n'			//—имвол конца строки 
#define IN_CODE_LIMITER '|'


#define IN_CODE_TABLE {\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*0-15*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*16-31*/\
	IN::A, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::Q, IN::A, IN::A, IN::A, IN::A, IN::A, IN::A, IN::F, IN::A,/*32-47*/\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::A, IN::F, IN::A, IN::F, IN::F,/*48-63*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*64-79*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*80-95*/\
	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,/*96-111*/\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::A, IN::F, IN::A, IN::F, IN::F,/*112-127*/\
   /*   0      1      2      3      4      5      6      7      8      9     10     11     12     13     14    15*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*128-143*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*144-159*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*160-175*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*176-191*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*192-207*/\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*208-223*/\
	IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R,/*224-239*/\
	IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, IN::R, '€',/*240-255*/\
			}
namespace In
{
    struct IN	//исходные данные
    {
        enum { T = 1024, F = 2048, I = 4096, A = 1025, R=1027, S=1028, Q=1029}; // T - допустимый символ, F - недопустимый, I - игнорировать, иначе заменить, ј-арифм знаки(дл€ удалени€ лишних пробелов ;,}{()=+-/* )
		//R- русские буквы (разрешено только в одинарных кавычках), S-пробел
        int size = 0;		// размер исходного кода
        int lines = 0;		// количество строк
        int ignor = 0;		// количество проигнорированных строк
        unsigned char* text;// исходный код (Windows - 1251)
        int code[256] = IN_CODE_TABLE;// таблица проверки: T, F, I новое значение
		std::vector<std::pair<int, std::string>> lexVector; //вектор
    };
    IN getin(wchar_t infile[], wchar_t outfile[]);	// ввести и проверить входной поток
};