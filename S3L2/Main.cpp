#define FLUSH while(getchar() != '\n')

#include <stdlib.h>
#include "stdio.h"
#include "time.h"

#include "Exceptions.h"

#include "CmdMgr/CmdMgr.h"

#include "Number.h"
#include "Sequence.h"
#include "AlphaIndex.h"
#include "IO.cpp"														
#include "Test.cpp"
#include "CmdBinds.cpp"

int main()
{
	FILE *ifstream = fopen("lol.txt", "r");
	Dict<String, int> &AlphaIndex = CreateAlphaIndex(ifstream, 20);

	Print(AlphaIndex);

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
