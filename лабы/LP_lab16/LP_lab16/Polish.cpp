#include "stdafx.h"

using namespace std;

bool PolishNotation(int i,LT::LexTable& lextable, IT::IdTable& idtable)
{
	stack<LT::Entry> stack;		// стек для операций
	queue<LT::Entry> queue;		// очередь для операндов
	LT::Entry temp;				// запрещенная лексема, все лишние элементы будут заменяться на нее
	temp.idxTI = -1;
	temp.lexema = '#';
	temp.sn = -1;
	LT::Entry func;
	func.lexema = '@';
	LT::Entry commas;
	int countComma = 0;			//подсчет количества запятых
	char* comma= new char[1]{ "" };
	int countLex = 0;			// количество преобразованных лексем
	int posLex = i;				// запоминаем номер лексемы перед преобразованием
	bool findFunc = false;


	for (i; lextable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
		switch (lextable.table[i].lexema)
		{
		case LEX_ID:	// если идентификатор
		{
			queue.push(lextable.table[i]);   // помещаем в очередь
			continue;
		}
		case LEX_LITERAL:		// если литерал
		{
			queue.push(lextable.table[i]);	// помещаем в очередь
			continue;
		}
		case LEX_LEFTHESIS:		// если (
		{
			if (idtable.table[lextable.table[i - 1].idxTI].idtype == IT::IDTYPE::F)
				findFunc = true;
			stack.push(lextable.table[i]); // помещаем ее в стек
			continue;
		}
		case LEX_RIGHTHESIS:	// если )
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
			while (stack.top().lexema != LEX_LEFTHESIS)	// пока не встретим (
			{
				queue.push(stack.top());	// выталкиваем из стека в очередь
				stack.pop();

				if (stack.empty())
					return false;
			}
			stack.pop();	// уничтожаем (
			continue;
		}
		case LEX_OPERATOR:	// если знак оператора
		{
			while (!stack.empty() && lextable.table[i].priority <= stack.top().priority)	// пока приоритет текущего оператора 
																								//меньше или равен приоритету оператора в вершине стека
			{
				queue.push(stack.top());	// выталкиваем со стека в выходную строку
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

	while (!stack.empty())	// если стек не пустой
	{
		if (stack.top().lexema == LEX_LEFTHESIS || stack.top().lexema == LEX_RIGHTHESIS)
			return false;
		queue.push(stack.top());	// выталкиваем все в очередь
		stack.pop();
	}

	while (countLex != 0)		// замена текущего выражения в таблице лексем на выражение в ПОЛИЗ
	{
		if (!queue.empty()) {
			lextable.table[posLex++] = queue.front();
			//cout << idtable.table[queue.front().idxTI].id;	// вывод в консоль
			queue.pop();
		}
		else
		{
			lextable.table[posLex++] = temp;			// может лучше перезаписать таблицу?
		}
		countLex--;
	}

	for (int i = 0; i < posLex; i++)		// восстановление индексов первого вхождения в таблицу лексем у операторов из таблицы идентификаторов
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