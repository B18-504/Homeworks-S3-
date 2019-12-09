#define FLUSH while(getchar() != '\n')

#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "Exceptions.h"

#include "CmdMgr/CmdMgr.h"

#include "Number.h"
#include "Sequence.h"
#include "BPlus.h"
#include "IO.cpp"														
#include "Test.cpp"
#include "CmdBinds.cpp"


int main()
{
	BPlus<int, int> a(5);

	a.Set(1, 3);
	a.Remove(1);

	printf("%d\n", a.IsPresent(1));

	srand(time(0));

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
