#include "Dictionary.h"
#include <iostream>
#include "pch.h"
namespace Dictionary
{
	Instance Create(const char name[DICTNAMEMAXSIZE], int size)
	{
		if (size > DICTMAXSIZE) throw THROW02;
		if ((sizeof(name) == DICTNAMEMAXSIZE) && (name[DICTNAMEMAXSIZE] != '\0')) throw THROW01;

		Instance in;
		strcpy(in.name, name);
		in.maxsize = size;
		in.size = 0;
		in.dictionary = new Entry[in.maxsize];
		return in;
	};

	void AddEntry(Instance& inst, Entry ed)
	{
		if (inst.size + 1 > inst.maxsize) throw THROW03;
		for (int i = 0; i < inst.size; i++)
			if (ed.id == inst.dictionary[i].id) throw THROW04;

		inst.dictionary[inst.size] = ed;
		inst.size++;
	};

	void DelEntry(Instance& inst, int id)
	{

		int a = -1;
		for (int i = 0; i < inst.size; i++)
		{
			if (inst.dictionary[i].id == id) { a = i; break; }
		}
		if (a < 0) throw THROW06;

		for (int i = a; i < inst.size; i++)
		{
			inst.dictionary[i] = inst.dictionary[i + 1];
		}
		inst.size--;
	};

	void UpdEntry(Instance& inst, int id, Entry new_ed)  ////-----------
	{
		int a = -1;

		for (int i = 0; i < inst.size; i++)
		{
			if (inst.dictionary[i].id == id) { a = i; }
		}

		if (a < 0) throw THROW07;

		inst.dictionary[a] = new_ed;

	};





	Entry GetEntry(Instance& inst, int id)
	{
		int a = -1;
		for (int i = 0; i < inst.size; i++)
		{
			if (inst.dictionary[i].id == id) { a = i; break; }
		}

		if (a < 0) throw THROW05;

		return  inst.dictionary[a];
	};

	void Print(Instance d)
	{
		printf("\n-------%s-------", d.name);
		for (int i = 0; i < d.size; i++)
		{
			printf("\n%d  \t%s", d.dictionary[i].id, d.dictionary[i].name);
		}
	};

	void Delete(Instance& d)    //---
	{
		d.size = 0;
		delete[] d.dictionary;
	};



}