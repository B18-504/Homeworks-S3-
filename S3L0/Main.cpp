#define FLUSH while(getchar() != '\n')

#include "stdlib.h"
#include "stdio.h"
#include <typeinfo>

#include "Exceptions.h"

#include "CmdMgr/CmdMgr.h"

#include "Number.h"
#include "Sequence.h"
#include "IO.cpp"
#include "CmdBinds.cpp"

using namespace std;

int main()
{
	HTable table;
	init(table);
	binds(table);
	try
	{
		binds(table);
	}
	catch(Exception E)
	{
		E.alert();
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
			E.alert();
		}
	}
	return 0;
}
