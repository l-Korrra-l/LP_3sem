#include "Lex.h"
namespace Lex
{
	void LEX(LT::LexTable& lt, IT::IdTable& it)
	{
		lextable = &lt;
		idTable = &it;
	}
	//void LEX::Delete()
	//{
	//	idTable->Delete();
	//	lextable->Delete();
	//	lextable = nullptr;
	//	idTable = nullptr;
	//}
}