#include "Parm.h"
#include "Error.h"
#include "Log.h"
#include "In.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <cwchar>
#include <fstream>
using namespace std;
#include "stdafx.h"
namespace Log
{
	//void WriteA(LOG log, bool fl, FST::FST fst, int line)
	//{
	//	if (fl)
	//		*log.stream << "Цепочка " << fst.string << " распознана" << endl;
	//	else *log.stream << "Цепочка " << fst.string << " не распознана" << std::endl;
	//}
	LOG getlog(wchar_t logfile[])
	{
		LOG newLog;
		newLog.stream = new ofstream;
		newLog.stream->open(logfile);
		if (!newLog.stream->is_open())
			throw ERROR_THROW(112);

		wcscpy_s(newLog.logfile, logfile);

		return newLog;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char** ptr = &c;
		while (**ptr != '\0')
		{
			*log.stream << *ptr;
			ptr++;
		}
		*log.stream << endl;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t** pointer = &c;
		while (*pointer != L"")
		{
			char buffer[256];
			size_t n = 0; 
			wcstombs_s(&n, buffer, *pointer, 256);
			*log.stream << buffer;
			pointer++;
		}
		*log.stream << endl;
	}

	void WriteLog(LOG log)
	{
		time_t t = time(0);
		tm currentTime;
		localtime_s(&currentTime, &t);
		char str[30];
		strftime(str, 30, "%d.%m.%Y %H:%M:%S", &currentTime);
		*log.stream << "===== Протокол ===== Дата:  " << str << "=====";
	}

	void WriteParm(LOG log, Parm::PARM par)
	{
		size_t n = 0;
		char buffer[256];
		*log.stream << "\n===== Параметры =====" << endl;
		wcstombs_s(&n, buffer, par.log, PARM_MAX_SIZE);	*log.stream << "-log: " << buffer << endl;
		wcstombs_s(&n, buffer, par.out, PARM_MAX_SIZE);	*log.stream << "-out: " << buffer << endl;
		wcstombs_s(&n, buffer, par.out, PARM_MAX_SIZE); *log.stream << "-in: " << buffer << endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "===== Исходные данные =====" << endl;
		*log.stream << "Количество символов: " << in.size+1 << endl;
		*log.stream << "Проигнорировано: " << in.ignor << endl;
		*log.stream << "Количество строк: " << in.lines+1 << endl;
	}

	void WriteError(LOG log, Error::ERROR newError)
	{
		if ( newError.id==122) *log.stream << "Ошибка " << newError.id << ": " << newError.message << ", строка " << newError.inext.line << ", лексема " << newError.inext.lex << endl;
		else
		if (newError.id == 121) *log.stream << "Ошибка " << newError.id << ": " << newError.message << ", строка " << newError.inext.line << endl;
		else if (log.stream == nullptr)
			cout << "Mistake" << newError.id << ": " << newError.message << ", строка " << newError.inext.line << ", позиция " << newError.inext.col << endl;
		else
			*log.stream << "Ошибка " << newError.id << ": " << newError.message << ", строка " << newError.inext.line << ", позиция " << newError.inext.col << endl;
	}


	void Close(LOG log)
	{
		if (log.stream != nullptr)
		{
			log.stream->close();
			delete log.stream;
		}
	}

	void WriteOut(Parm::PARM parm, In::IN in)
	{
		ofstream outFile;
		outFile.open(parm.out);
		if (!outFile) throw ERROR_THROW(101);
		outFile << in.text;
		outFile.close();
	}

	void PrintLexTable(LOG log, LT::LexTable& lexTable)
	{
		if ((*log.stream).is_open())
		{
			*log.stream << "+==========================+" << endl;
			*log.stream << "|     ТАБЛИЦА  ЛЕКСЕМ      |" << endl;
			*log.stream << "+==========================+" << endl;
			*log.stream
				<< '|' << std::setw(4) << "№" << "|"
				<< setw(10) << "Лексема" << "|"
				<< setw(10) << "№ стр." << "|" << endl;
			*log.stream << "+==========================+" << endl;
			LT::Entry entry;
			for (int i = 0; i < lexTable.size; i++)
			{
				entry = GetEntry(lexTable,i);
				*log.stream << '|' << std::setw(4) << i
					<< '|' << setw(10) << entry.lexema
					<< "|" << setw(10) << entry.sn
					<< '|' << endl;
			}
			*log.stream << "+==========================+" << std::endl;
			*log.stream << std::endl << std::endl;
		}
		else ERROR_THROW(112)
	}

	void ShowLexTable(LT::LexTable& lexTable)
	{

			cout << "+==========================+" << endl;
			cout << "|     ТАБЛИЦА  ЛЕКСЕМ      |" << endl;
			cout << "+==========================+" << endl;
			cout
				<< '|' << std::setw(4) << "№" << "|"
				<< setw(10) << "Лексема" << "|"
				<< setw(10) << "№ стр." << "|" << endl;
			cout << "+==========================+" << endl;
			LT::Entry entry;
			for (int i = 0; i < lexTable.size; i++)
			{
				entry = GetEntry(lexTable, i);
				cout << '|' << std::setw(4) << i
					<< '|' << setw(10) << entry.lexema
					<< "|" << setw(10) << entry.sn
					<< '|' << endl;
				
			}
			cout << "+==========================+" << std::endl;
			cout << std::endl << std::endl;

	}


	void ShowLex(LT::LexTable& lexTable)
	{

		
		LT::Entry entry;
		int count = 0;
		for (int i = 0; i < lexTable.size; i++)
		{
			entry = GetEntry(lexTable, i);
			if (entry.sn > count)
			{
				count++;
				cout << endl <<entry.sn << ' ' ;
			}
			cout<< entry.lexema;

		}
	
		cout << std::endl << std::endl;

	}

	void PrintIdTable(LOG& log, IT::IdTable& idTable)
	{
		if ((*log.stream).is_open())
		{
			*log.stream << "+=================================================+" << std::endl;
			*log.stream << "|              ТАБЛИЦА ИНДЕТИФИКАТОРОВ            |" << std::endl;
			*log.stream << "+=================================================+" << std::endl;
			*log.stream << '|' << std::setw(3) << "№: " << "|" << std::setw(8) << "ID: " << '|'
				<< std::setw(8) << "№ в ТЛ." << '|' << std::setw(16) << "Тип ID" << '|' <<
				std::setw(10) << "Тип знач." << '|' << std::endl; //<< std::setw(24) << "Знач." << '|'

			*log.stream << "+=================================================+" << std::endl;
			for (int i = 0; i < idTable.size; i++)
			{
				IT::Entry entry = GetEntry(idTable,i);
				std::string idDataType = "";
				std::string idType = "";
				std::string parentBlock = "";
#pragma region Type
				switch (entry.iddatatype)
				{
				case IT::IDDATATYPE::INT :
					idDataType = "integer";
					break;
				case IT::IDDATATYPE::STR:
					idDataType = "string";
					break;
				default:
					idDataType = "undef";
					break;
				}

				switch (entry.idtype)
				{
				case IT::IDTYPE::V:
					idType = "переменная";
					break;
				case IT::IDTYPE::F:
					idType = "функция";
					break;
				case IT::IDTYPE::P:
					idType = "параметр";
					break;
				case IT::IDTYPE::L:
					idType = "литерал";
					break;
				default:
					idType = "undef";
					break;
				}



#pragma endregion
				* log.stream << '|' << std::setw(3) << i << "|" << std::setw(8) << entry.id << '|'
					<< std::setw(8) << entry.idxfirstLE << '|' << std::setw(16) << idType << '|'
					<< std::setw(10) << idDataType << '|';

				//if (entry.iddatatype == IT::IDDATATYPE::INT)
				//{
				//	*log.stream << std::setw(24) << entry.value.vint << '|';
				//}
				//else
				//{
				//	*log.stream << std::setw(24) << entry.value.vstr->str << '|';
				//}
				*log.stream << std::endl;
			}

			*log.stream << "+=================================================+" << std::endl;
		}
		else ERROR_THROW(112)
	}

	void ShowIdTable(IT::IdTable& idTable)
	{
			cout << "+============================================================+" << std::endl;
			cout << "|                   ТАБЛИЦА  ИНДЕТИФИКАТОРОВ                 |" << std::endl;
			cout << "+============================================================+" << std::endl;
			cout << '|' << std::setw(3) << "№: " << "|" << std::setw(8) << "ID: " << '|'
				<< std::setw(8) << "№ в ТЛ." << '|' << std::setw(16) << "Тип ID" << '|' <<
				std::setw(10) << "Тип знач." << '|'<< std::setw(10)<<"Обл. вид."<<'|' << std::endl; //<< std::setw(24) << "Знач." << '|'

			cout << "+============================================================+" << std::endl;
			for (int i = 0; i < idTable.size; i++)
			{
				IT::Entry entry = GetEntry(idTable, i);
				std::string idDataType = "";
				std::string idType = "";
				std::string parentBlock = "";
#pragma region Type
				switch (entry.iddatatype)
				{
				case IT::IDDATATYPE::INT:
					idDataType = "integer";
					break;
				case IT::IDDATATYPE::STR:
					idDataType = "string";
					break;
				default:
					idDataType = "undef";
					break;
				}

				switch (entry.idtype)
				{
				case IT::IDTYPE::V:
					idType = "переменная";
					break;
				case IT::IDTYPE::F:
					idType = "функция";
					break;
				case IT::IDTYPE::P:
					idType = "параметр";
					break;
				case IT::IDTYPE::L:
					idType = "литерал";
					break;
				default:
					idType = "undef";
					break;
				}



#pragma endregion
				cout << '|' << std::setw(3) << i << "|" << std::setw(8) << entry.id << '|'
					<< std::setw(8) << entry.idxfirstLE << '|' << std::setw(16) << idType << '|'
					<< std::setw(10) << idDataType << '|' << std::setw(10)<< entry.scope<<'|';

				//if (entry.iddatatype == IT::IDDATATYPE::INT)
				//{
				//	*log.stream << std::setw(24) << entry.value.vint << '|';
				//}
				//else
				//{
				//	*log.stream << std::setw(24) << entry.value.vstr->str << '|';
				//}
				cout << std::endl;
			}

			cout << "+============================================================+" << std::endl;

	}
}