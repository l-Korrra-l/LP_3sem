#pragma once
#include <fstream>
#include "In.h"
#include "Error.h"
#include "Parm.h"
#include "FST.h"
namespace Log // ������ � ����������
{
	struct LOG	// ��������
	{
		wchar_t logfile[PARM_MAX_SIZE]; // ��� ����� ������
		std::ofstream* stream;			// �������� ����� ���������
	};

	static const LOG INITLOG = { L"", NULL }; //��������� ��� ��������� ������������� LOG
	LOG getlog(wchar_t logfile[]);	//������������ �������� LOG
	void WriteLine(LOG log, char* c, ...);// ������� � �������� ������������� �����
	void WriteLine(LOG log, wchar_t* c, ...); // ������� � ������ ������������� �����
	void WriteLog(LOG log); //������� � ������ ���������
	void WriteParm(LOG log, Parm::PARM parm); // ������� � �������� ���������� � ������� ����������
	void WriteIn(LOG log, In::IN in); //������� � �������� ���������� � ������� ������
	void WriteError(LOG log, Error::ERROR error); // ������� � �������� ���������� �� ������
	void Close(LOG log);// ������� ��������
	//void WriteA(LOG log, bool fl, FST::FST fst, int line);
	void WriteOut(Parm::PARM parm, In::IN in);
	void PrintLexTable(LOG log, LT::LexTable& lexTable);
	void PrintIdTable(LOG& log, IT::IdTable& in);
	void ShowLexTable(LT::LexTable& lexTable);
	void ShowLex(LT::LexTable& lexTable);
	void ShowIdTable(IT::IdTable& in);
};
