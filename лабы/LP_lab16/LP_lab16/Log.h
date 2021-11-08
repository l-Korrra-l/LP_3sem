#pragma once
#include <fstream>
#include "In.h"
#include "Error.h"
#include "Parm.h"
#include "FST.h"
namespace Log // Работа с протоколом
{
	struct LOG	// Протокол
	{
		wchar_t logfile[PARM_MAX_SIZE]; // Имя файла потока
		std::ofstream* stream;			// Выходной поток протокола
	};

	static const LOG INITLOG = { L"", NULL }; //Структура для начальной инициализации LOG
	LOG getlog(wchar_t logfile[]);	//Сформировать стрктуру LOG
	void WriteLine(LOG log, char* c, ...);// вывести в протокол конкантенацию строк
	void WriteLine(LOG log, wchar_t* c, ...); // вывести в прокол конкантенацию строк
	void WriteLog(LOG log); //вывести в прокол заголовок
	void WriteParm(LOG log, Parm::PARM parm); // вывести в протокол информацию о входных параметрах
	void WriteIn(LOG log, In::IN in); //вывести в протокол информацию о входном потоке
	void WriteError(LOG log, Error::ERROR error); // Вывести в протокол информацию об ошибке
	void Close(LOG log);// закрыть протокол
	//void WriteA(LOG log, bool fl, FST::FST fst, int line);
	void WriteOut(Parm::PARM parm, In::IN in);
	void PrintLexTable(LOG log, LT::LexTable& lexTable);
	void PrintIdTable(LOG& log, IT::IdTable& in);
	void ShowLexTable(LT::LexTable& lexTable);
	void ShowLex(LT::LexTable& lexTable);
	void ShowIdTable(IT::IdTable& in);
};
