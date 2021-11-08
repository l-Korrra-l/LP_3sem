#include <iostream>
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "Lex.h"
#include "Error.h"
#include "Polish.h"
#include <fstream>
#include "stdafx.h"

std::string to_string(int n) {
	char buf[40];
	sprintf_s(buf, n < 10 ? "0%d" : "%d", n);
	return buf;
}
namespace FST {

	RELATION::RELATION(char c, short nn)
	{
		symbol = c;			
		nnode = nn;			
	};

	NODE::NODE()
	{
		n_relation = 0;	
		RELATION* relations = NULL;
	};

	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	};

	FST::FST(short ns, char s,  NODE n, ...)
		: symbol(s), position(-1), nstates(ns)
	{			
		nodes = new NODE[ns];		
		NODE* p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates];	
		memset(rstates, 0xff, sizeof(short) * nstates); 
		rstates[0] = 0;
	};

	bool step(FST& fst, short*& rstates, std::string str)
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; ++i)
			if (rstates[i] == fst.position)
			{
				for (short j = 0; j < fst.nodes[i].n_relation; ++j)
				{
					if (fst.nodes[i].relations[j].symbol == (unsigned char)str[fst.position]) 
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				}
			}

		return rc;
	}

	bool execute(FST& fst, std::string str) {
		short* rstates = new short[fst.nstates];
		short lstring = (short)str.size();
		bool rc = true;

		memset(rstates, 0xff, sizeof(short) * fst.nstates);

		fst.position = -1;
		*fst.rstates = 0;

		for (short i = 0; i < lstring && rc; ++i) {
			fst.position++;
			rc = step(fst, rstates, str);
		}
		delete[] rstates;

		return rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc;
	}

	void Analysis(std::vector<std::pair<int, std::string>> vec, std::ostream* logfile, std::ofstream* outputFile, LT::LexTable& lextable, IT::IdTable& idtable, LEX::Lex& lex)
	{
//Переменные
		std::string str = "01 ", temp_prefix = "", current_prefix = "";
		IT::IDTYPE idtype = IT::IDTYPE::V;
		IT::IDDATATYPE iddatatype = IT::IDDATATYPE::INT;
		FST fst_arr[] = { FST_MAIN , FST_PRINT , FST_RETURN , FST_DECLARE , FST_INTEGER , FST_STRING , FST_FUNCTION ,
			FST_LEFT_BRACKET , FST_RIGHT_BRACKET , FST_LEFT_BRACE , FST_RIGHT_BRACE , FST_PLUS , FST_MINUS , FST_MULTI ,
			FST_DIVISION , FST_COMMA, FST_SEMICOLON, FST_EQUALLY, FST_NUMBERS, FST_ID, FST_STRING_LITERAL };
		int size = sizeof(fst_arr) / sizeof(FST);
		bool decl = false;
		bool param = false;
		int isMain = 0;


//Разбор лексем
		for (size_t i = 0; i < vec.size(); i++) {
			if (i >= 1 && vec[i - 1].first < vec[i].first)
				str += IN_CODE_ENDL + to_string(vec[i].first) + ' ';
			for (int j = 0; j < size; j++) {
				if (execute(fst_arr[j], vec[i].second)) {
					decl = false;
					str += fst_arr[j].symbol;
					int it_id = IT::IsId(idtable, vec[i].second.c_str(), current_prefix.c_str());
					//Определение префикса
					if (fst_arr[j].symbol == LEX_MAIN) {isMain++;
								if (isMain > 1) throw ERROR_THROW_LEX(121, vec[i].first, vec[i].second);}
					if (fst_arr[j].symbol == LEX_FUNCTION || fst_arr[j].symbol == LEX_MAIN) {
						if (current_prefix.empty())
							if (fst_arr[j].symbol == LEX_MAIN)
							{
								current_prefix = vec[i].second;
							}
							else
								current_prefix = vec[i + 1].second;
						else
						{
							temp_prefix = current_prefix;
							current_prefix = vec[i + 1].second;
						}
						param = true;
					}

					if (fst_arr[j].symbol == LEX_RIGHTHESIS) {
						if (!temp_prefix.empty())
							current_prefix = temp_prefix;
						else
							temp_prefix.clear();
						param = false;
					}
					else if (fst_arr[j].symbol == LEX_BRACELET) {
						current_prefix.clear();
						temp_prefix.clear();
					}
#pragma endregion

#pragma region "Определение IDTYPE"
					if ((fst_arr[j].symbol == LEX_ID || fst_arr[j].symbol == LEX_MAIN) && i >= 2) {
						if (lextable.table[lextable.size - 2].lexema == LEX_DECLARE) {
							decl = true;
							idtype = IT::IDTYPE::V;
						}
						else if (fst_arr[j].symbol == LEX_MAIN || lextable.table[lextable.size - 1].lexema == LEX_FUNCTION) {
							idtype = IT::IDTYPE::F;
							decl = true;
						}
						else if (param) {
							idtype = IT::IDTYPE::P;
							decl = true;
						}
					}
					else if (fst_arr[j].symbol == LEX_LITERAL) {
						idtype = IT::IDTYPE::L;
						decl = true;
					}
#pragma endregion

#pragma region "Определение IDDATATYPE"
					int delt = 0;
					if ((fst_arr[j].symbol == LEX_ID) && i >= 2) {
						if (lextable.table[lextable.size - 1].lexema == LEX_FUNCTION)
							delt = 2;
						else if (lextable.table[lextable.size - 1].lexema == LEX_INTEGER)
							delt = 1;
						if (vec[i - delt].second == INTEGER)
							iddatatype = IT::IDDATATYPE::INT;
						else if (vec[i - delt].second == STRING)
							iddatatype = IT::IDDATATYPE::STR;
					}
					else if (fst_arr[j].symbol == LEX_LITERAL) {
						if (execute(fst_arr[20], vec[i].second)) iddatatype = IT::IDDATATYPE::STR;
						else
						iddatatype = IT::IDDATATYPE::INT;
					}
#pragma endregion

					#pragma region "Заполнение таблиц"
					
										if (fst_arr[j].symbol == LEX_ID && !decl && it_id == -1) {
											throw ERROR_THROW_LEX(122, vec[i].first , vec[i].second);
										}
					
										if ((fst_arr[j].symbol == LEX_ID || fst_arr[j].symbol == LEX_LITERAL || fst_arr[j].symbol == LEX_MAIN) && it_id == TI_NULLIDX) {
											if (fst_arr[j].symbol == LEX_LITERAL) {
												IT::Add(idtable, { lextable.size, vec[i].second.c_str(), "", iddatatype, idtype });
												LT::Add(lextable, { fst_arr[j].symbol, vec[i].first, it_id });
											}
											else {
												IT::Add(idtable, { lextable.size, vec[i].second.c_str(), current_prefix != vec[i].second ? current_prefix.c_str() : "", iddatatype, idtype });
												LT::Add(lextable, { fst_arr[j].symbol, vec[i].first, idtable.size });
											}
										}
										else
											LT::Add(lextable, { fst_arr[j].symbol, vec[i].first, it_id });
					#pragma endregion
					break;
				}
				else if (j == size - 1)
				throw ERROR_THROW_LEX(122, vec[i].first, vec[i].second);
			}
		}
		if (isMain == 0) throw ERROR_THROW(120);
		* outputFile << str;
		lex.idTable = idtable;
		lex.lextable = lextable;
	};
	
}