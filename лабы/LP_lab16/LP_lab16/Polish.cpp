#include "stdafx.h"

using namespace std;

bool PolishNotation(int i,LT::LexTable& lextable, IT::IdTable& idtable)
{
	stack<LT::Entry> stack;		// ���� ��� ��������
	queue<LT::Entry> queue;		// ������� ��� ���������
	LT::Entry temp;				// ����������� �������, ��� ������ �������� ����� ���������� �� ���
	temp.idxTI = -1;
	temp.lexema = '#';
	temp.sn = -1;
	LT::Entry func;
	func.lexema = '@';
	LT::Entry commas;
	int countComma = 0;			//������� ���������� �������
	char* comma= new char[1]{ "" };
	int countLex = 0;			// ���������� ��������������� ������
	int posLex = i;				// ���������� ����� ������� ����� ���������������
	bool findFunc = false;


	for (i; lextable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
		switch (lextable.table[i].lexema)
		{
		case LEX_ID:	// ���� �������������
		{
			queue.push(lextable.table[i]);   // �������� � �������
			continue;
		}
		case LEX_LITERAL:		// ���� �������
		{
			queue.push(lextable.table[i]);	// �������� � �������
			continue;
		}
		case LEX_LEFTHESIS:		// ���� (
		{
			if (idtable.table[lextable.table[i - 1].idxTI].idtype == IT::IDTYPE::F)
				findFunc = true;
			stack.push(lextable.table[i]); // �������� �� � ����
			continue;
		}
		case LEX_RIGHTHESIS:	// ���� )
		{
			if (findFunc)
			{
				//comma[0] = ++countComma;
				//errno_t _itoa_s(++countComma, comma, sizeof(comma), 10);
				commas.lexema = (char)++countComma+48;
				//errno_t strcpy(commas.lexema, comma);
				stack.push(commas);
				stack.push(func);
				findFunc = false;
			}
			while (stack.top().lexema != LEX_LEFTHESIS)	// ���� �� �������� (
			{
				queue.push(stack.top());	// ����������� �� ����� � �������
				stack.pop();

				if (stack.empty())
					return false;
			}
			stack.pop();	// ���������� (
			continue;
		}
		case LEX_OPERATOR:	// ���� ���� ���������
		{
			while (!stack.empty() && lextable.table[i].priority <= stack.top().priority)	// ���� ��������� �������� ��������� 
																								//������ ��� ����� ���������� ��������� � ������� �����
			{
				queue.push(stack.top());	// ����������� �� ����� � �������� ������
				stack.pop();
			}
			stack.push(lextable.table[i]);
			continue;
		}
		case LEX_COMMA:
		{
			countComma++;
			continue;
		}
		}
	}

	while (!stack.empty())	// ���� ���� �� ������
	{
		if (stack.top().lexema == LEX_LEFTHESIS || stack.top().lexema == LEX_RIGHTHESIS)
			return false;
		queue.push(stack.top());	// ����������� ��� � �������
		stack.pop();
	}

	while (countLex != 0)		// ������ �������� ��������� � ������� ������ �� ��������� � �����
	{
		if (!queue.empty()) {
			lextable.table[posLex++] = queue.front();
			//cout << idtable.table[queue.front().idxTI].id;	// ����� � �������
			queue.pop();
		}
		else
		{
			lextable.table[posLex++] = temp;			// ����� ����� ������������ �������?
		}
		countLex--;
	}

	for (int i = 0; i < posLex; i++)		// �������������� �������� ������� ��������� � ������� ������ � ���������� �� ������� ���������������
	{
		if (lextable.table[i].lexema == LEX_OPERATOR || lextable.table[i].lexema == LEX_LITERAL)
			idtable.table[lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}

void PolishStart(LT::LexTable& lextable, IT::IdTable& idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == '=')
		{
			PolishNotation(i+1, lextable, idtable);
		}
	}
}