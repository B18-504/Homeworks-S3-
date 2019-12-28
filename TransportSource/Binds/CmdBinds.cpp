#pragma once

//#include "Classes.cpp"
#include "FileCmds.cpp"
#include "IntCmds.cpp"
#include "TransportCmds.cpp"

void InputPrint(void ***argv)
{
	printf("%s", **(char***)argv);
}

void NewLine(void ***)
{
	printf("\n");
}




void binds(HTable &table)
{
	char err;
	
	bindt(table, "file", sizeof(FILE*));
	bindt(table, "int", sizeof(int));

	bindvt(table, "TransportGraph", err);
	bindvt(table, "Route", err);
			
	char **types;
	
	set(types, 5);

	types[5] = 0;

	copy(types[0], "TransportGraph", err);
	copy(types[1], "Route", err);
	copy(types[2], "int", err);
	copy(types[3], "int", err);
	copy(types[4], "int", err);

	bindf(table, GetRoute, "GetRoute", types, err);




	types[2] = 0;
	
	copy(types[0], "file", err);
	copy(types[1], "input", err);
	
	bindf(table, StartInFile, "StartInFile", types, err);
	bindf(table, StartOutFile, "StartOutFile", types, err);




	types[1] = 0;
	
	copy(types[0], "file", err);
	
	bindf(table, StopFile, "StopFile", types, err);

	copy(types[0], "int", err);

	bindf(table, InputInt, "Input", types, err);
	bindf(table, PrintInt, "Print", types, err);

	copy(types[0], "TransportGraph", err);

	bindf(table, InputTransportGraph, "Input", types, err);

	copy(types[0], "Route", err);

	bindf(table, PrintRoute, "Print", types, err);

	copy(types[0], "input", err);

	bindf(table, InputPrint, "Print", types, err);


	
	
	types[0] = 0;

	bindf(table, NewLine, "NewLine", types, err);
}
