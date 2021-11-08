#pragma once
#define ID_MAXSIZE 5
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255

namespace IT
{
	enum class IDDATATYPE
	{
		INT = 1, STR = 2
	};
	enum class IDTYPE
	{
		V = 1,                        //переменная
		F = 2,                        //функция
		P = 3,                        //параметр
		L = 4                         //литерал
	};
	struct Entry
	{
		int idxfirstLE;               //индекс первой строки в ТЛ
		char id[ID_MAXSIZE];          //идентификатор
		char scope[10];
		IDDATATYPE iddatatype;        //тип данных
		IDTYPE idtype;                //тип идентификатора
		Entry* view = NULL;
		union Value
		{
			int vint;
			struct String
			{
				unsigned char len;
				char str[TI_STR_MAXSIZE];

			}vstr;
		}value;
		Entry() = default;
		Entry(int idxfirstLE, const char* id, const char* scope, IDDATATYPE iddatatype, IDTYPE idtype);
	};
	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
		void Delete();
	};
	IdTable Create(int size);
	void Add(IdTable& idtable, const Entry& entry);
	Entry GetEntry(IdTable& idtable,int n);
	int IsId(IdTable& idtable, const char id[ID_MAXSIZE], const char prefix[10]);
	void Delete(IdTable& idtable);

}