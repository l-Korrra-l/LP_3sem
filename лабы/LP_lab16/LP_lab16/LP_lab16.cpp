#include "stdafx.h"
int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "Rus");
    Log::LOG log = Log::INITLOG;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN inner = In::getin(parm.in, parm.out);
        Log::WriteIn(log, inner);
        LT::LexTable lextable = LT::Create(inner.lexVector.size());
        IT::IdTable idtable = IT::Create(inner.lexVector.size());
        LEX::Lex lex;
        lex.idTable = idtable;
        lex.lextable = lextable;
        Log::WriteOut(parm, inner);
        //std::cout << inner.text << std::endl;
        std::ofstream outputFile(parm.out);
        // Lex::LEX lex=
        FST::Analysis(inner.lexVector, log.stream, &outputFile, lextable, idtable, lex);
        Log::ShowIdTable(idtable);
        PolishStart(lex);
        Log::ShowLex(lextable);
        // MFST_TRACE_START
        unsigned int start_time = clock();

        //MFST::Mfst mfst(lex, GRB::getGreibach());
        //mfst.start();
        //unsigned int end_time = clock();
        //unsigned int search_time = end_time - start_time;
        //std::cout << search_time << std::endl;
        //mfst.savededucation();
        //mfst.printrules();
        Log::Close(log);
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
    }

    system("pause");
    return 0;
}