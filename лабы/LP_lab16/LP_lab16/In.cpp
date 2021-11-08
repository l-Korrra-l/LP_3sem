#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "fstream"
#include <iostream>
using namespace std;

void writeToVector(std::vector<std::pair<int, std::string>>& vector, std::string& string, const int& line)
{
	if (!string.empty())
	{
		vector.push_back({ line, string });
	}
	string.clear();
}
namespace In
{
	IN getin(wchar_t infile[], wchar_t outfile[])
	{
		setlocale(LC_CTYPE,"Rus");
		int col = 0;
		IN newIn;
		newIn.text = new unsigned char[IN_MAX_LEN_TEXT];
		newIn.size = 0;
		unsigned char let;
		int i = 0;
		bool rusFlag = false;

		ifstream file(infile);
		ofstream out_file(outfile);
		if (!out_file.is_open()) throw ERROR_THROW(113);
		if (!file.is_open()) throw ERROR_THROW(110)
		else
		{

		for (i = 0; !file.eof(); i++)
			{
				let = file.get();
				if (let == IN_CODE_ENDL)
				{
					newIn.text[i] = IN_CODE_LIMITER; i++; newIn.size++;
					newIn.text[i] = let; 
					newIn.size++;
					newIn.lines++;
					col = 0;
				}
				else
				{
					switch (newIn.code[let])
					{
					case IN::T:
					{
						newIn.text[i] = let; 
						newIn.size++;
						col++;
						break;
					}
					case IN::Q:
					{
						rusFlag = !rusFlag;
						newIn.text[i] = let;
						newIn.size++;
						col++;
						break;
					}
					case IN::F:
					{ throw ERROR_THROW_IN(111, newIn.lines, col);  break; }    
					case IN::A:
					{
						if (newIn.text[i - 1] == ' ')
						{
							i--; newIn.text[i] = let; 
							break;
						}
						else if ((newIn.code[newIn.text[i-1]] == IN::A)&& (let == ' ')) { i--;  break; }
						else {
							newIn.text[i] = let;
							newIn.size++;
							col++;
							break;
						}
					}
					case IN::R:
					{
						if (rusFlag == true)
						{
							newIn.text[i] = let;
							newIn.size++;
							col++;
							break;
						}
						else { throw ERROR_THROW_IN(130, newIn.lines, col);  break; }
					}
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
		    newIn.text[newIn.size-1] = IN_CODE_LIMITER; newIn.text[newIn.size] = '\0'; 

			file.close();

			string tempLex = "";
			newIn.lines = 1;
			for (int i = 0; i < newIn.size; i++)
			{
				if (newIn.text[i] == ' ' || newIn.text[i] == IN_CODE_ENDL)
				{
					writeToVector(newIn.lexVector, tempLex, newIn.lines);
				}
				else if (newIn.code[newIn.text[i]] == newIn.T || newIn.code[newIn.text[i]] == newIn.R)
				{
					tempLex += newIn.text[i];
				}

				else if (newIn.code[newIn.text[i]] == IN::A)
				{
					writeToVector(newIn.lexVector, tempLex, newIn.lines);
					tempLex += newIn.text[i];
					writeToVector(newIn.lexVector, tempLex, newIn.lines);
				}
				else if (newIn.code[newIn.text[i]] == IN::Q)
				{
					do
					{
						tempLex += newIn.text[i];
						i++;
					} while (newIn.code[newIn.text[i]] != IN::Q);
					tempLex += newIn.text[i];
					i++;
				}
				if (newIn.text[i] == IN_CODE_LIMITER)
				{
					writeToVector(newIn.lexVector, tempLex, newIn.lines);
					newIn.lines++;
				}
			}
			out_file << newIn.text;
			out_file.close();
		}
		return newIn;
		
	}
}