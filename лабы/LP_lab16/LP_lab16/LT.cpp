#include "LT.h"
#include "Error.h"
#include "In.h"
#include <fstream>

namespace LT
{
	LexTable Create(int size) {
		if (size > LT_MAXSIZE)
			throw ERROR_THROW(113);
		LT::LexTable lextable;
		lextable.size = 0;
		lextable.maxsize = size;
		lextable.table = new Entry[size];
		return lextable;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.maxsize == lextable.size)
			throw ERROR_THROW(113);
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}
	void LexTable::Delete()
	{
		delete[] table;
		table = nullptr;
	}
}