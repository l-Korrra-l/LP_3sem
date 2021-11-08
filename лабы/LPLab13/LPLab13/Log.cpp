#include "Parm.h"
#include "Error.h"
#include "Log.h"
#include "In.h"
#include "fstream"
#include <iostream>
#include <ctime>
#include <cwchar>
using namespace std;

namespace Log
{
	void WriteA(LOG log, bool fl, FST::FST fst, int line)
	{
		if (fl)
			*log.stream << "Цепочка " << fst.string << " распознана" << endl;
		else *log.stream << "Цепочка " << fst.string << " не распознана" << std::endl;
	}
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
		*log.stream << "Количество символов: " << in.size << endl;
		*log.stream << "Проигнорировано: " << in.ignor << endl;
		*log.stream << "Количество строк: " << in.lines << endl;
	}

	void WriteError(LOG log, Error::ERROR newError)
	{
		if (log.stream == nullptr)
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
}