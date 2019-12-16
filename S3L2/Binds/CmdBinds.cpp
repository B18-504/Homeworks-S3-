#pragma once

//#include "Classes.cpp"
#include "FileCmds.cpp"
#include "IntCmds.cpp"
#include "DictCmds.cpp"

void TestSequence(void ***)
{
	TestSequence();
}




void binds(HTable &table)
{
	char err;
																		//Виртуальные типы можно привязывать как обычные
	bindt(table, "file", sizeof(FILE*));								//Перед использованием СТРОГО необходимо вызвать инициализирующую функцию
	bindt(table, "int", sizeof(int));									//Тк инициализация объекта абстрактного типа недопустима

	bindvt(table, "Dict<str:int>", err);																											
	bindvt(table, "Dict<int:int>", err);								//Привязка виртуальных типов через специальный интерфейс
																		//При создании экземпляра виртуального типа будет создан пустой объект (ptr = 0)
			
	char **types;
	
	set(types, 3);

	types[3] = 0;

	copy(types[0], "Dict<int:int>", err);
	copy(types[1], "int", err);
	copy(types[2], "int", err);

	bindf(table, DictIsPresent<int, int>, "IsPresent", types, err);
	bindf(table, DictGet<int, int>, "Get", types, err);
	bindf(table, DictSet<int, int>, "Set", types, err);

	copy(types[0], "Dict<str:int>", err);
	copy(types[1], "int", err);
	copy(types[2], "file", err);

	bindf(table, AlphaIndex, "AlphaIndex", types, err);




	types[2] = 0;
	
	copy(types[0], "file", err);
	copy(types[1], "input", err);
	
	bindf(table, StartInFile, "StartInFile", types, err);
	bindf(table, StartOutFile, "StartOutFile", types, err);

	copy(types[0], "Dict<int:int>", err);
	copy(types[1], "int", err);

	bindf(table, StartBPlusDict<int, int>, "StartBPlusDict<int:int>", types, err);
	bindf(table, DictGetCount<int, int>, "GetCount", types, err);
	bindf(table, DictCurrentCap<int, int>, "CurrentCap", types, err);
	bindf(table, DictRemove<int, int>, "Remove", types, err);
	
	


	types[1] = 0;
	
	copy(types[0], "file", err);
	
	bindf(table, StopFile, "StopFile", types, err);

	copy(types[0], "int", err);

	bindf(table, InputInt, "Input", types, err);
	bindf(table, PrintInt, "Print", types, err);

	copy(types[0], "Dict<int:int>", err);

	bindf(table, InputDict<int, int>, "Input", types, err);
	bindf(table, PrintDict<int, int>, "Print", types, err);

	copy(types[0], "Dict<str:int>", err);

	bindf(table, PrintDict<String, int>, "Print", types, err);


	
	
	types[0] = 0;
	
	bindf(table, (void (*)())TestSequence, "TestSequence", types, err);
}
