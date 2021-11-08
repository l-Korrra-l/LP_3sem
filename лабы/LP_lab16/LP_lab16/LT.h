#pragma once
#define LEXEMA_FIXSIZE 1         //фиксированный размер лексемы
#define LT_MAXSIZE 4096          //максимальоне количесвто строк в таблице лексем
#define LT_TI_NULLIDX 0xffffff   //нет элемента таблицы идентификаторов 
#define LEX_INTEGER 't'         //лексема для integer
#define LEX_STRING 't'          //лексема для string
#define LEX_ID 'i'         //лексема для идентификатора
#define LEX_LITERAL 'l'         //лексема для литерала
#define LEX_FUNCTION 'f'         //лексема для function
#define LEX_DECLARE 'd'         //лексема для declare
#define LEX_RETURN 'r'         //лексема для return
#define LEX_PRINT 'p'         //лексема для print
#define LEX_SEMICOLON ';'         //лексема для ;
#define LEX_COMMA ','         //лексема для .
#define LEX_LEFTBRACE '{'         //лексема для { 
#define LEX_BRACELET '}'         //лексема для } 
#define LEX_LEFTHESIS '('         //лексема для ( 
#define LEX_RIGHTHESIS ')'         //лексема для )
#define LEX_PLUS 'v'         //лексема для +
#define LEX_MINUS 'v'         //лексема для -
#define LEX_STAR 'v'         //лексема для *
#define LEX_DIRSLASH 'v'         //лексема для /
#define LEX_OPERATOR 'v'         //лексема для /
#define LEX_MAIN 'm'
#define LEX_SIGN 'v' 

namespace LT {

	struct Entry {
		char lexema;                                       
		int sn;                                               //номер строки в исходном тексте
		int idxTI;                                            //индекс в ТИ
		int priority;

	};
	struct LexTable                                        //экземляр таблицы лексе
	{
		int maxsize;								//емкость таблицы лексем < LT_MAXSIZE
		int size;
		Entry* table;
		void Delete();
	};

	LexTable Create(int size); //*
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);				//номер получаемой строки
	void Delete(LexTable& lextable);

}
