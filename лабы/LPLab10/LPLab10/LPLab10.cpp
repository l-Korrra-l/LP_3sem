#include <iostream>
#include <locale>
#include <cwchar>
#include <windows.h>

#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    //cout << "---- test Error::geterror   ---" << endl << endl;
    //try
    //{
    //    throw ERROR_THROW(100);
    //}
    //catch (Error::ERROR e)
    //{
    //    cout << "Mistake " << e.id << ": " << e.message << endl << endl;
    //}

    //std::cout << "---- test Error::geterrorin  ---" << std::endl << std::endl;
    //try
    //{
    //    throw ERROR_THROW_IN(111, 7, 7);
    //}
    //catch (Error::ERROR e)
    //{
    //    std::cout << "Mistake " << e.id << ": " << e.message
    //        << ", Line " << e.inext.line
    //        << ", position " << e.inext.col << std::endl << std::endl;
    //};

    //try
    //{
    //    throw ERROR_THROW_IN(111, 7, 7);
    //}
    //catch (Error::ERROR e)
    //{
    //    cout << "Mistake " << e.id << ": " << e.message << ", line" << e.inext.line << ", pos " << e.inext.col << endl << endl;
    //}

    //cout << "---- test Parm::getparam   ---" << endl << endl;
    //try
    //{
    //    Parm::PARM parm = Parm::getparm(argc, argv);
    //    wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << endl << endl;
    //}
    //catch (Error::ERROR e)
    //{
    //    cout << "Mistake " << e.id << ": " << e.message << endl << endl;
    //};

    std::cout << "----  test In::getin   ----\n\n";
    try {

        Parm::PARM parm = Parm::getparm(argc, argv);
        In::IN inner = In::getin(parm.in);
        std::cout << inner.text << std::endl;
        std::cout << "Всего символов: " << inner.size << std::endl;
        std::cout << "Всего строк " << inner.lines << std::endl;
        std::cout << "Пропущено: " << inner.ignor << std::endl;
        delete[] inner.text;
    }
    catch (Error::ERROR e) {
        std::cout << "Ошибка " << e.id << ": " << e.message << std::endl;
        std::cout << "Строка " << e.inext.line << " позиция " << e.inext.col << std::endl << std::endl;
    }


    //Log::LOG log = Log::INITLOG;
    //try
    //{
    //    Parm::PARM parm = Parm::getparm(argc, argv);
    //    log = Log::getlog(parm.log);
    //    char test[] = "Тест", noMis[] = " без ошибок ", space[] = "";
    //    Log::WriteLine(log, test, noMis, space);
    //    Log::WriteLog(log);
    //    Log::WriteParm(log, parm);
    //    In::IN in = In::getin(parm.in);
    //    Log::WriteIn(log, in);
    //    Log::Close(log);
    //}
    //catch (Error::ERROR e)
    //{
    //    Log::WriteError(log, e);
    //}

    system("pause");
    return 0;
}
