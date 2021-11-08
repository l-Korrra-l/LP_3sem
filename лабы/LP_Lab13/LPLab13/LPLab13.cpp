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
    Log::LOG log = Log::INITLOG;
    setlocale(LC_ALL, "Rus");
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        In::IN inner = In::getin(parm.in);
        std::cout << inner.text << std::endl;
        std::cout << "Всего символов: " << inner.size << std::endl;
        std::cout << "Всего строк " << inner.lines << std::endl;
        std::cout << "Пропущено: " << inner.ignor << std::endl;
        Log::WriteLine(log,(char*)"--------Результат анализа------");
        char* pch = strtok((char*)inner.text, "|");
        int line = 0;
        while (pch != NULL)
        {
            line++;
            FST::FST fst(pch,9, regularExpr);
            bool fl = FST::execute(fst);
            if (fl)
                std::cout << "Цепочка " << fst.string << " распознана" << std::endl;
            else std::cout << "Цепочка " << fst.string << " не распознана" << std::endl;
             Log::WriteA(log,fl,fst,line);
            pch = strtok(NULL,"|");
        }
        Log::Close(log);
    }
    catch (Error::ERROR e) {
        std::cout << "Ошибка " << e.id << ": " << e.message << std::endl;
        std::cout << "Строка " << e.inext.line << " позиция " << e.inext.col << std::endl << std::endl;
    }
    system("pause");
    return 0;
}

