#pragma once

#include "Classes.cpp"

void printnum(void ***argv)
{
	if(**argv)
	{
		printf("%s\n", ((Number*)(**argv))->ValueAsStr());
	}
	else
	{
		throw NPE();
	}
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
		throw BCI();
	}
}

void fprintnum(void ***argv)
{
	if(*(argv[0]))
	{
		fprintf((FILE*)(*(argv[1])), "%s\n", ((Number*)(*(argv[0])))->ValueAsStr());
	}
	else
	{
		throw NPE();
	}
}

void finputnum(void ***argv)
{
	char **words;
	unsigned char n;
	char err;
	finput(words, (FILE*)(*(argv[1])), n, err);
	if((!err) * (n == 1))
	{
		(*(argv[0])) = StrToNumber(*words);
	}
	else
	{
		throw BFI();
	}
}




void inputseq(void ***argv)
{
	/*
	char **words;
	unsigned char n;
	char err;
	input(words, n, err);
	if(!err)
	{
		try
		{
			((Sequence<Number>*)(**argv))->SetFromStr(words, n);
		}
		catch(Exception E)
		{
			((Sequence<Number>*)(**argv))->Clear();
			throw E;
		}
	}
	else
	{
		throw BCI();
	}
	*/
}

void printseq(void ***argv)
{
	Sequence<Number>::Slider &sl = ((Sequence<Number>*)(**argv))->InitSlider(0);
	if(sl.IsBound())
	{
		try
		{
M:			printf("%s ", sl.GetVal().ValueAsStr());					//бесконечный цикл, только не говорите, что нечитаемо
			sl.ShiftRight();
			goto M;
		}
		catch(Exception E)
		{
			printf("\n");
			if(E.code != 0x12)
			{
				throw E;
			}
		}
	}
	else
	{
		printf("Empty sequence\n");
	}
}

void finputseq(void ***argv)
{
	/*char **words;
	unsigned char n;
	char err;
	finput(words, (FILE*)(*(argv[1])), n, err);
	if(!err)
	{
		try
		{
			((Sequence<Number>*)(**argv))->SetFromStr(words, n);
		}
		catch(Exception E)
		{
			((Sequence<Number>*)(**argv))->Clear();
			throw E;
		}
	}
	else
	{
		throw BFI();
	}
	*/
}

void fprintseq(void ***argv)
{
	if(!bool(*(argv[1])))
	{
		throw FSE();
	}
	Sequence<Number>::Slider &sl = ((Sequence<Number>*)(*(argv[0])))->InitSlider(0);
	if(sl.IsBound())
	{
		try
		{
M:			fprintf((FILE*)(*(argv[1])), "%s ", sl.GetVal().ValueAsStr());					//бесконечный цикл, только не говорите, что нечитаемо
			sl.ShiftRight();
			goto M;
		}
		catch(Exception E)
		{
			fprintf((FILE*)(*(argv[1])), "\n");
			if(E.code != 0x12)
			{
				throw E;
			}
		}
	}
	else
	{
		printf("Empty sequence\n");
	}
}

void randinputseq(void ***argv)
{
	if(*(argv[2]))
	{
		((Sequence<Number>*)(*(argv[0])))->SetRandVals(*(argv[1]), ((Number*)(*(argv[2])))->ValueAsInt());
	}
	else
	{
		throw NPE();
	}
}





void GetLen(void ***argv)
{
	delete (Number*)(*(argv[1]));
	*(argv[1]) = new Int;
	((Int*)(*(argv[1])))->body = ((Sequence<Number>*)(*(argv[0])))->GetLen();
}

void IsEmpty(void ***argv)
{
	delete (Number*)(*(argv[1]));
	*(argv[1]) = new Bool;
	((Bool*)(*(argv[1])))->body = ((Sequence<Number>*)(*(argv[0])))->IsEmpty();
}

void IsSorted(void ***argv)
{
	delete (Number*)(*(argv[2]));
	*(argv[2]) = new Bool;
	((Bool*)(*(argv[2])))->body = ((Sequence<Number>*)(*(argv[0])))->IsSorted(((char (*)(Number&, Number&))(*(argv[1]))));
}

void QuickSort(void ***argv)
{
	QuickSort(*(Sequence<Number>*)(*(argv[0])), ((char (*)(Number&, Number&))(*(argv[1]))));
}

void InsertSort(void ***argv)
{
	InsertSort(*(Sequence<Number>*)(*(argv[0])), ((char (*)(Number&, Number&))(*(argv[1]))));
}

void Get(void ***argv)
{
	Sequence<Number> *seq = *argv[0];
	int i = ((Number*)(*(argv[1])))->ValueAsInt();
	Number *tmp = &((*seq)[i]);									//arg2 = arg0[arg1]
	delete (Number*)(*(argv[2]));
	*(argv[2]) = tmp;
	tmp = 0;
	seq = 0;
}

void GetFirst(void ***argv)
{
	Number *tmp = &(((Sequence<Number>*)(*(argv[0])))->GetFirst());			//arg1 = arg0.GetFirst()
	delete (Number*)(*(argv[1]));
	*(argv[1]) = tmp;
	tmp = 0;
}

void GetLast(void ***argv)
{
	Number *tmp = &(((Sequence<Number>*)(*(argv[0])))->GetLast());
	delete (Number*)(*(argv[1]));
	*(argv[1]) = tmp;
	tmp = 0;
}

void Append(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Append(*((Number*)(*(argv[1]))));		//arg0.Append(arg1)
}

void Prepend(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Prepend(*((Number*)(*(argv[1]))));
}

void Insert(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Insert(*((Number*)(*(argv[2]))), ((Number*)(*(argv[1])))->ValueAsInt());		//arg0.insert(arg2, arg1)
}

void Remove(void ***argv)
{
	((Sequence<Number>*)(*(argv[0])))->Remove(*((Number*)(*(argv[1]))));	//arg0.Remove(arg1)
}

void GetSubS(void ***argv)
{
	Sequence<Number> *tmp = ((Sequence<Number>*)(*(argv[0])))->GetSubS(((Number*)(*(argv[2])))->ValueAsInt(), ((Number*)(*(argv[3])))->ValueAsInt());	//arg1 = arg1.GetSubS(arg2, arg3)
	delete (Sequence<Number>*)(*(argv[1]));
	*(argv[1]) = tmp;
}




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
	
	bindt(table, "number", sizeof(Number*));							//Виртуальные типы можно привязывать как обычные
	bindt(table, "file", sizeof(FILE*));								//Перед использованием СТРОГО необходимо вызвать инициализирующую функцию
																		//Тк инициализация объекта абстрактного типа недопустима
																		
	bindvt(table, "sequence", err);										
	bindit(table, "array", "sequence", generateArray, err);
	bindit(table, "list", "sequence", generateListSequence, err);		//Привязка виртуальных типов через специальный интерфейс
																		//Создание возможно ТОЛЬКО указанием имплементирующего типа
	char **types;
	
	set(types, 4);
	
	copy(types[0], "sequence", err);
	copy(types[1], "sequence", err);
	copy(types[2], "number", err);
	copy(types[3], "number", err);
	
	bindf(table, GetSubS, "getsubs", types, err);
	
	
	
	types[3] = 0;
	
	copy(types[0], "sequence", err);
	copy(types[1], "number", err);
	copy(types[2], "number", err);
	
	bindf(table, Get, "Get", types, err);
	bindf(table, Insert, "Insert", types, err);

	copy(types[1], "numbergenerator", err);

	bindf(table, randinputseq, "SetRand", types, err);

	copy(types[1], "cmp", err);

	bindf(table, IsSorted, "IsSorted", types, err);
	
	
	
	types[2] = 0;
	
	copy(types[0], "sequence", err);
	copy(types[1], "number", err);
	
	bindf(table, GetLen, "GetLen", types, err);
	bindf(table, IsEmpty, "IsEmpty", types, err);
	bindf(table, GetFirst, "GetFirst", types, err);
	bindf(table, GetLast, "GetLast", types, err);
	bindf(table, Append, "Append", types, err);
	bindf(table, Prepend, "Prepend", types, err);
	bindf(table, Remove, "Remove", types, err);

	copy(types[1], "cmp", err);

	bindf(table, (void (*)(void***))QuickSort, "QuickSort", types, err);
	bindf(table, (void (*)(void***))InsertSort, "InsertSort", types, err);
	
	copy(types[0], "file", err);
	copy(types[1], "input", err);
	
	bindf(table, StartInFile, "StartInFile", types, err);
	bindf(table, StartOutFile, "StartOutFile", types, err);
	
	copy(types[0], "number", err);
	copy(types[1], "file", err);
	
	bindf(table, finputnum, "Input", types, err);
	bindf(table, fprintnum, "Print", types, err);
	
	copy(types[0], "sequence", err);
	
	bindf(table, finputseq, "Input", types, err);
	bindf(table, fprintseq, "Print", types, err);
	
	
	
	
	types[1] = 0;
	
	copy(types[0], "number", err);
	
	bindf(table, printnum, "Print", types, err);
	bindf(table, inputnum, "Input", types, err);
	
	copy(types[0], "file", err);
	
	bindf(table, StopFile, "StopFile", types, err);
	
	copy(types[0], "sequence", err);
	
	bindf(table, inputseq, "Input", types, err);
	bindf(table, printseq, "Print", types, err);
	
	
	
	
	types[0] = 0;
	
	bindf(table, (void (*)())TestSequence, "TestSequence", types, err);



	bind(table, RandInt, "randint", "numbergenerator");
	bind(table, RandDouble, "randdouble", "numbergenerator");

	bind(table, (char (*)(Number&, Number&))GreatOrEquals<Int>, "greatoreqint", "cmp");
	bind(table, (char (*)(Number&, Number&))LessOrEquals<Int>, "lessoreqint", "cmp");

	bind(table, (char (*)(Number&, Number&))GreatOrEquals<Double>, "greatoreqdouble", "cmp");
	bind(table, (char (*)(Number&, Number&))LessOrEquals<Double>, "lessoreqdouble", "cmp");
}
