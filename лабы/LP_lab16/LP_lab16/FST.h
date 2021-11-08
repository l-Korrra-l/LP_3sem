#pragma once
#include <iostream>
#include "IT.h"
#include "LT.h"
#include "Lex.h"
#include <string>
#include <vector>
#define INTEGER "integer"
#define STRING "string"
namespace FST
{
	struct RELATION
	{
		unsigned char symbol;
		short nnode;
		RELATION(
			char c = 0x00,
			short ns = NULL
		);
	};

	struct NODE
	{
		short n_relation;
		RELATION* relations;
		NODE();
		NODE( short n, RELATION rel, ...);
	};

	struct FST
	{		
		short position;
		short nstates;
		char symbol;
		char* string;
		NODE* nodes;
		short* rstates;
		FST(short ns, char s,  NODE n, ...);
	};

	bool execute(FST& fst, std::string str);

	void Analysis(std::vector<std::pair<int, std::string>> vec, std::ostream* logfile, std::ofstream* outputFile, LT::LexTable& lextable, IT::IdTable& idtable, LEX::Lex& lex);
};