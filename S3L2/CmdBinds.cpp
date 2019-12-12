#pragma once

//#include "Classes.cpp"


void TestSequence(void ***)
{
	TestSequence();
}

void StartInFile(void ***argv)
{
	(*(argv[0])) = fopen((char*)(*(argv[1])), "r");
	if(!bool(*(argv[0])))
	{
		throw FSE();
	}
}

void StartOutFile(void ***argv)
{
	(*(argv[0])) = fopen((char*)(*(argv[1])), "w");
	if(!bool(*(argv[0])))
	{
		throw FSE();
	}
}

void StopFile(void ***argv)
{
	if(bool(*(argv[0])))
	{
		fclose(*(argv[0]));
		*(argv[0]) = 0;
	}
}











void binds(HTable &table)
{
	char err;
																		//Виртуальные типы можно привязывать как обычные
	bindt(table, "file", sizeof(FILE*));								//Перед использованием СТРОГО необходимо вызвать инициализирующую функцию
	bindt(table, "int", sizeof(int));									//Тк инициализация объекта абстрактного типа недопустима
																												
																		//Привязка виртуальных типов через специальный интерфейс
																		//При создании экземпляра виртуального типа будет создан пустой объект (ptr = 0)
			
	char **types;
	
	set(types, 2);
	
	types[2] = 0;
	
	copy(types[0], "file", err);
	copy(types[1], "input", err);
	
	bindf(table, StartInFile, "StartInFile", types, err);
	bindf(table, StartOutFile, "StartOutFile", types, err);
	
	


	types[1] = 0;
	
	copy(types[0], "file", err);
	
	bindf(table, StopFile, "StopFile", types, err);
	
	
	
	
	types[0] = 0;
	
	bindf(table, (void (*)())TestSequence, "TestSequence", types, err);
}
