#include "stdio.h"
#include "locale.h"

#include "CmdMgr.h"
#include "CmdBinds.cpp"




int main()
{
	setlocale(0, "RUS");
	HTable table;
	init(table);
	
	char err;
	char **types;
	
	set(types, 1, err);
	
	copy(types[0], "int", err);
	bindf(table, dupi, "dup", types, err);
	bindf(table, inpi, "input", types, err);
	bindf(table, printi, "print", types, err);
	
	copy(types[0], "double", err);
	bindf(table, dupd, "dup", types, err);
	bindf(table, inpd, "input", types, err);
	bindf(table, printd, "print", types, err);
	
	bindt(table, "int", sizeof(int), err);
	bindt(table, "double", sizeof(double), err);
	
	
	bool finish = 0;
	while(!finish)
	{
		getcmd(table, finish);
	}
	
	return 0;
}
