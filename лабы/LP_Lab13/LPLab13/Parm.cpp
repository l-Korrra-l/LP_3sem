#include "Parm.h"
#include "Error.h"
#include <tchar.h>

namespace Parm
{

	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM newParm{};
		bool in = 0, out = 0, log = 0;
	
		for (int i = 1; i < argc; i++)
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);

		if (argc == 1)
			throw ERROR_THROW(100);


		for (int i = 1; i < argc; i++)
		{
			wchar_t* parm = argv[i];
			if (wcsstr(parm, PARM_IN) == parm)
			{
				in = 1;
				wcscpy_s(newParm.in, parm + wcslen(PARM_IN));
			}
			if (wcsstr(parm, PARM_OUT) == parm)
			{
				out = 1;
				wcscpy_s(newParm.out, parm + wcslen(PARM_OUT));
			}
			if (wcsstr(parm, PARM_LOG) == parm)
			{
				log = 1;
				wcscpy_s(newParm.log, parm + wcslen(PARM_LOG));
			}
		}

		if (!in) throw ERROR_THROW(100);
		if (!out)
		{
			wcscpy_s(newParm.out, newParm.in);
			wcsncat_s(newParm.out, PARM_MAX_SIZE, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
		}
		if (!log)
		{
			wcscpy_s(newParm.log, newParm.in);
			wcsncat_s(newParm.log, PARM_MAX_SIZE, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
		}
		return newParm;
		
	};

}