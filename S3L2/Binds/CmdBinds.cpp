#pragma once

//#include "Classes.cpp"
#include "FileCmds.cpp"
#include "IntCmds.cpp"
#include "DictCmds.cpp"
#include "DictIteratorCmds.cpp"

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
	bindvt(table, "Dict<int:int>::Iterator", err);						//При создании экземпляра виртуального типа будет создан пустой объект (ptr = 0)
			
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

	bindf(table, StartBPlusDict<int, int>, "StartBPlusDict", types, err);
	bindf(table, DictGetCount<int, int>, "GetCount", types, err);
	bindf(table, DictCurrentCap<int, int>, "CurrentCap", types, err);
	bindf(table, DictRemove<int, int>, "Remove", types, err);

	copy(types[0], "Dict<str:int>", err);

	bindf(table, StartBPlusDict<String, int>, "StartBPlusDict", types, err);

	copy(types[0], "Dict<int:int>", err);
	copy(types[1], "Dict<int:int>::Iterator", err);

	bindf(table, StartIterator<int, int>, "StartIterator", types, err);

	copy(types[0], "Dict<int:int>::Iterator", err);
	copy(types[1], "int", err);

	bindf(table, IteratorGet<int, int>, "Get", types, err);
	bindf(table, IteratorGetKey<int, int>, "GetKey", types, err);
	bindf(table, IteratorSet<int, int>, "Set", types, err);
	bindf(table, IteratorHasNext<int, int>, "HasNext", types, err);
	bindf(table, IteratorHasPrev<int, int>, "HasPrev", types, err);

	
	

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

	copy(types[0], "Dict<int:int>::Iterator", err);

	bindf(table, IteratorShiftLeft<int, int>, "ShiftLeft", types, err);
	bindf(table, IteratorShiftRight<int, int>, "ShiftRight", types, err);


	
	
	types[0] = 0;
	
	bindf(table, (void (*)())TestSequence, "TestSequence", types, err);
}
