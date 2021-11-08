#pragma once
#define LEXEMA_FIXSIZE 1         //������������� ������ �������
#define LT_MAXSIZE 4096          //������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffff   //��� �������� ������� ��������������� 
#define LEX_INTEGER 't'         //������� ��� integer
#define LEX_STRING 't'          //������� ��� string
#define LEX_ID 'i'         //������� ��� ��������������
#define LEX_LITERAL 'l'         //������� ��� ��������
#define LEX_FUNCTION 'f'         //������� ��� function
#define LEX_DECLARE 'd'         //������� ��� declare
#define LEX_RETURN 'r'         //������� ��� return
#define LEX_PRINT 'p'         //������� ��� print
#define LEX_SEMICOLON ';'         //������� ��� ;
#define LEX_COMMA ','         //������� ��� .
#define LEX_LEFTBRACE '{'         //������� ��� { 
#define LEX_BRACELET '}'         //������� ��� } 
#define LEX_LEFTHESIS '('         //������� ��� ( 
#define LEX_RIGHTHESIS ')'         //������� ��� )
#define LEX_PLUS 'v'         //������� ��� +
#define LEX_MINUS 'v'         //������� ��� -
#define LEX_STAR 'v'         //������� ��� *
#define LEX_DIRSLASH 'v'         //������� ��� /
#define LEX_OPERATOR 'v'         //������� ��� /
#define LEX_MAIN 'm'
#define LEX_SIGN 'v' 

namespace LT {

	struct Entry {
		char lexema;                                       
		int sn;                                               //����� ������ � �������� ������
		int idxTI;                                            //������ � ��
		int priority;

	};
	struct LexTable                                        //�������� ������� �����
	{
		int maxsize;								//������� ������� ������ < LT_MAXSIZE
		int size;
		Entry* table;
		void Delete();
	};

	LexTable Create(int size); //*
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);				//����� ���������� ������
	void Delete(LexTable& lextable);

}
