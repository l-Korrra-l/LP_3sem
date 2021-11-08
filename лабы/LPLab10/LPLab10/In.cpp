#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "fstream"
#include <iostream>
using namespace std;
namespace In
{
	IN getin(wchar_t infile[])
	{
		setlocale(LC_CTYPE,"Rus");
		int col = 0;
		IN newIn;
		newIn.text = new unsigned char[IN_MAX_LEN_TEXT];
		unsigned char let;
		int i = 0;
		unsigned char a = newIn.code[208];
		ifstream file(infile);
		if (!file.is_open()) throw ERROR_THROW(110)
		else
		{
			//let = file.get(); 
			//let = file.get();
			//let = file.get();
		for (i = 0; !file.eof() ; i++)
			//while (let = file.get()), newIn.lines<2 
			{
				let = file.get();
				//cout << let;
				if (let == IN_CODE_ENDL)
				{
					newIn.text[i] = let;
					newIn.lines++;
					col = 0;
				}
				else 
				{
					switch (newIn.code[let])
					{
					case newIn.T:
					{
						newIn.text[i] = let;
						newIn.size++;
						col++;
						break;
					}

					case newIn.F:
					{ throw ERROR_THROW_IN(111, newIn.lines, col); break; }
					case newIn.I:
					{
						newIn.ignor++;
						col++;
						break;
					}
					default:
					{
						newIn.text[i] = newIn.code[let];
						newIn.size++;
						col++;
						break;
					}

					}
				}
				
			
			}	
		newIn.text[newIn.size+1] = '\0';
		//cout << "\n";
			file.close();
		
		}
		return newIn;
		
	}
}