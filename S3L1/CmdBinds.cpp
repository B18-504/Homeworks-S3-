#pragma once

#include "Classes.cpp"

void printnum(void ***argv)
{
	printf("%s\n", ((Number*)(**argv))->ValueAsStr());
}

void inputnum(void ***argv)
{
	char **words;
	unsigned char n;
	char err;
	input(words, n, err);
	if((!err) * (n == 1))
	{
		(**argv) = StrToNumber(*words);
	}
	else
	{
		throw(BCI());
	}
}

void GetLen(void ***argv)
{
	delete (Number*)(*(argv[1]));
	*(argv[1]) = new Uint;
	((Uint*)(*(argv[1])))->body = ((Sequence<Number>*)(*(argv[0])))->GetLen();
}

void IsEmpty(void ***argv)
{
	delete (Number*)(*(argv[1]));
	*(argv[1]) = new Bool;
	((Bool*)(*(argv[1])))->body = ((Sequence<Number>*)(*(argv[0])))->IsEmpty();
}

void Get(void ***argv)
{
	Sequence<Number> *seq = *argv[0];
	uint u = ((Number*)(*(argv[1])))->ValueAsUint();
	Number *tmp = (*seq)[u]->Clone();		//arg2 = arg0[arg1]
	delete (Number*)(*(argv[2]));
	*(argv[2]) = tmp;
	tmp = 0;
	seq = 0;
}

void GetFirst(void ***argv)
{
	Number *tmp = ((Sequence<Number>*)(*(argv[0])))->GetFirst()->Clone();			//arg1 = arg0.GetFirst()
	delete (Number*)(*(argv[1]));
	*(argv[1]) = tmp;
	tmp = 0;
}

void GetLast(void ***argv)
{
	Number *tmp = ((Sequence<Number>*)(*(argv[0])))->GetLast()->Clone();
	delete (Number*)(*(argv[1]));
	*(argv[1]) = tmp;
	tmp = 0;
}

void Append(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Append(((Number*)(*(argv[1])))->Clone());		//arg0.Append(arg1)
}

void Prepend(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Prepend(((Number*)(*(argv[1])))->Clone());
}

void Insert(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Insert((Number*)(*(argv[2])), ((Number*)(*(argv[1])))->ValueAsUint());		//arg0.insert(arg2, arg1)
}

void Remove(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Remove((Number*)(*(argv[1])));	//arg0.Remove(arg1)
}

void GetSubS(void ***argv)
{
	Sequence<Number> *tmp = ((Sequence<Number>*)(*(argv[0])))->GetSubS(((Number*)(*(argv[2])))->ValueAsUint(), ((Number*)(*(argv[3])))->ValueAsUint());	//arg1 = arg1.GetSubS(arg2, arg3)
	delete (Sequence<Number>*)(*(argv[1]));
	*(argv[1]) = tmp;
}

void bTest1(void ***)
{
	Test1();
}

void binds(HTable &table)
{
	char err;
	
	bindt(table, "number", sizeof(Number*), err);						//Виртуальные типы можно привязывать как обычные
																		//Перед использованием СТРОГО необходимо вызвать инициализирующую функцию
	bindvt(table, "sequence", err);										//Тк инициализация объекта абстрактного типа недопустима
	bindit(table, "array", "sequence", generateArray, err);
	bindit(table, "list", "sequence", generateList, err);				//Привязка виртуальных типов через специальный интерфейс
																		//Создание возможно ТОЛЬКО указанием имплементирующего типа
	char **types;
	set(types, 0, err);
	
	bindf(table, bTest1, "test1", types, err);
	
	set(types, 1, err);
	
	copy(types[0], "number", err);
	
	bindf(table, printnum, "print", types, err);
	bindf(table, inputnum, "input", types, err);
	
	set(types, 2, err);
	
	copy(types[0], "sequence", err);
	copy(types[1], "number", err);
	
	bindf(table, GetLen, "getlen", types, err);
	bindf(table, IsEmpty, "isempty", types, err);
	bindf(table, GetFirst, "getfirst", types, err);
	bindf(table, GetLast, "getlast", types, err);
	bindf(table, Append, "append", types, err);
	bindf(table, Prepend, "prepend", types, err);
	bindf(table, Remove, "remove", types, err);
	
	set(types, 3, err);
	
	copy(types[0], "sequence", err);
	copy(types[1], "number", err);
	copy(types[2], "number", err);
	
	bindf(table, Get, "get", types, err);
	bindf(table, Insert, "insert", types, err);
	
	set(types, 4, err);
	
	copy(types[0], "sequence", err);
	copy(types[1], "sequence", err);
	copy(types[2], "number", err);
	copy(types[3], "number", err);
	
	bindf(table, GetSubS, "getsubs", types, err);
}
