#include "IT.h"
#include "Error.h"
#include <fstream>
#include <iomanip>
using namespace std;

namespace IT
{

	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE) throw ERROR_THROW(114);
			return { size, 0, new Entry[size] };
	}

	Entry::Entry(int idxfirstLE, const char* id, const char* scope, IDDATATYPE iddatatype, IDTYPE idtype)
		: idxfirstLE(idxfirstLE), idtype(idtype), iddatatype(iddatatype), value({ NULL })
	{
		for (int i = 0; i < ID_MAXSIZE; i++)
			this->id[i] = id[i];

		for (int i = 0; i < 10; i++)
			this->scope[i] = scope[i];

		this->id[ID_MAXSIZE - 1] = '\0';
		this->scope[10 - 1] = '\0';
	}
	void Add(IdTable& idtable, const Entry& entry)
	{
		if (idtable.size == idtable.maxsize) throw ERROR_THROW(114);
		idtable.table[idtable.size] = entry;
		idtable.size++;

	}

	Entry GetEntry(IdTable& idTable, int n)
	{
		if (n < idTable.maxsize && n >= 0)
			return idTable.table[n];
	}

	int IsId(IdTable& idtable, const char id[ID_MAXSIZE], const char prefix[10])
	{
		bool is_found = false;
		for (int i = 0; i < idtable.size; i++) {
			for (size_t j = 0; j < strlen(idtable.table[i].id); j++) {
				is_found = false;
				if (idtable.table[i].id[j] == id[j])
					is_found = true;
				else
					break;
			}
			if (is_found)
				for (size_t j = 0; j < strlen(idtable.table[i].scope); j++) {
					is_found = false;
					if (idtable.table[i].scope[j] == prefix[j])
						is_found = true;
					else
						break;
				}
			if (is_found)
				return i;
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable* idtable)
	{
		delete idtable->table;
		delete idtable;
	}

	void IdTable::Delete()
	{
		delete[] table;
		table = nullptr;
	}
}