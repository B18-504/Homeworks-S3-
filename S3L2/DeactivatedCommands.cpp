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
	if(**argv)
	{
		Sequence<Number>::Slider &sl = ((Sequence<Number>*)(**argv))->InitSlider(0);
		if(sl.IsBound())
		{
			try
			{
M:				printf("%s ", sl.GetVal().ValueAsStr());					//бесконечный цикл, только не говорите, что нечитаемо
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
