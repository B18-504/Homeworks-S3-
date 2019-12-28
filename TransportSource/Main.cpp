#define FLUSH while(getchar() != '\n')

#include <stdlib.h>
#include "stdio.h"
#include "time.h"
#include "locale.h"

#include "Exceptions.h"

#include "CmdMgr/CmdMgr.h"

#include "TransportGraph.h"
#include "IO.cpp"
#include "Binds/CmdBinds.cpp"

int main()
{
	setlocale(0, "RUS");
	
	HTable table;
	init(table);
	try
	{
		binds(table);
	}
	catch(Exception E)
	{
		printf("%s\n", E.message);
		return 1;
	}
	bool finish = 0;
	while(!finish)
	{
		try
		{
			getcmd(table, finish);
		}
		catch(Exception E)
		{
			printf("%s\n", E.message);
		}
	}
	return 0;
}
