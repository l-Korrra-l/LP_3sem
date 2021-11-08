#include <iostream>
#include "FST.h"
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "Log.h"

#define regularExpr FST::NODE(1, FST::RELATION('r',1)),\
                    FST::NODE(2, FST::RELATION(' ',1),FST::RELATION('b',2)),\
                    FST::NODE(2, FST::RELATION(' ',2),FST::RELATION(' ',3)),\
                    FST::NODE(2, FST::RELATION('p',4),FST::RELATION('c',4)),\
                    FST::NODE(1, FST::RELATION(';',5)),\
                    FST::NODE(3, FST::RELATION('b',2), FST::RELATION('e',7), FST::RELATION(' ',6)),\
                    FST::NODE(2, FST::RELATION('e',7),  FST::RELATION(' ',6)),\
                    FST::NODE(1, FST::RELATION(';',8)),\
                    FST::NODE()

int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "Hello World!\n";
}

    