#pragma once

bool isdigit(char c)
{
	return ((c > 47) * (c < 58));
}

Number *StrToNumber(char *str)
{
	bool first = 1, point = 0, b;
	double mul = 1;
	char err = 0;
	
	
	double dbl = 0;
	int in = 0;
	bool bl;
	
	if(cmp(str, "true"))
	{
		return new Bool(true);
	}
	
	if(cmp(str, "false"))
	{
		return new Bool(false);
	}
	
	
	--str;
	do
	{
		++str;
		if((first) * (*str == '-'))
		{
			mul = -1;
			first = 0;
		}
		else if(isdigit(*str))
		{
			first = 0;
			if((mul == 1) * ((in*10 + *str - 48) >= in))
			{
				in *= 10;
				in += *str - 48;
			}
			else if((mul == -1) * ((in*10 - *str + 48) <= in))
			{
				in *= 10;
				in -= *str - 48;
			}
			else
			{
				err = 1;
			}
		}
		else if((*str == 0)*(!first))
		{
			return new Int(in);
		}
		else
		{
			err = 1;
		}
	} while(!err);
	
	err = 0;
	
	dbl = in;
	
	--str;
	do
	{
		if (point)
		{
			mul /= 10;
		}
		++str;
		if ((first) * (*str == '-'))
		{
			mul = -1;
			first = 0;
		}
		else if ((!point) * (*str == '.'))
		{
			point = 1;
			first = 0;
		}
		else if (isdigit(*str))
		{
			first = 0;
			if (!point)
				dbl *= 10;
			dbl += mul * (*str - 48);
		}
		else if ((*str == 0)*(!first))
		{
			return new Double(dbl);
		}
		else
		{
			err = 1;
		}
	} while (!err);
	
	throw(BSF());
}

void Print(int a)
{
	printf("%d", a);
}

void Print(const String &a)
{
	printf("%s", a.body);
}

void FPrint(int a, FILE *file)
{
	fprintf(file, "%d", a);
}

void FPrint(const String &a, FILE *file)
{
	fprintf(file, "%s", a.body);
}

template <typename K, typename T>
void Print(Dict<K, T> &a)
{
	if(a.GetCount())
	{
		typename Dict<K, T>::Iterator &I = a.StartIterator();
		while(I.HasNext())
		{
			Print(I.GetKey());
			printf(": ");
			Print(I.Get());
			printf("\n");
			I.ShiftRight();
		}

		Print(I.GetKey());
		printf(": ");
		Print(I.Get());
		printf("\n");

		delete &I;
	}
	else
	{
		printf("Empty dictionary\n");
	}
}

template <typename K, typename T>
void FPrint(Dict<K, T> &a, FILE *file)
{
	if(a.GetCount())
	{
		typename Dict<K, T>::Iterator &I = a.StartIterator();
		while(I.HasNext())
		{
			FPrint(I.GetKey(), file);
			fprintf(file, ": ");
			FPrint(I.Get(), file);
			fprintf(file, "\n");
			I.ShiftRight();
		}

		FPrint(I.GetKey(), file);
		fprintf(file, ": ");
		FPrint(I.Get(), file);
		fprintf(file, "\n");

		delete &I;
	}
	else
	{
		fprintf(file, "Empty dictionary\n");
	}
}

void StrToT(int &a, char *str)
{
	bool first = 1;
	int mul = 1;
	char err = 0;
	a = 0;

	--str;

	do
	{
		++str;
		if((first) * (*str == '-'))
		{
			mul = -1;
			first = 0;
		}
		else if(isdigit(*str))
		{
			first = 0;
			if((mul == 1) * ((a*10 + *str - 48) >= a))
			{
				a *= 10;
				a += *str - 48;
			}
			else if((mul == -1) * ((a*10 - *str + 48) <= a))
			{
				a *= 10;
				a -= *str - 48;
			}
			else
			{
				err = 1;
			}
		}
		else if((*str == 0)*(!first))
		{
			err = 2;
		}
		else
		{
			err = 1;
		}
	} while(!err);
	if(err == 1)
	{
		throw BSF();
	}
}

template <typename K, typename T>
void InputPair(K &key, T &value)
{
	char **str;
	int l;
	char err;
	input(str, l, err);
	if(!err)
	{
		if(l == 2)
		{
			StrToT(key, str[0]);
			StrToT(value, str[1]);
		}
		else
		{
			throw BSF();
		}
	}
	else
	{
		throw BCI();
	}
}

template <typename K, typename T>
void FInputPair(K &key, T &value, FILE *file)
{
	char **str;
	int l;
	char err;
	finput(str, file, l, err);
	if(!err)
	{
		if(l == 2)
		{
			StrToT(key, str[0]);
			StrToT(value, str[1]);
		}
		else
		{
			throw BSF();
		}
	}
	else
	{
		throw BFI();
	}
}

void Input(int &a)
{
	char **str;
	int l;
	char err;
	input(str, l, err);

	if(err)
	{
		throw BCI();
	}

	if(l == 1)
	{
		StrToT(a, *str);
	}
	else
	{
		throw BSF();
	}	
}

void FInput(int &a, FILE *file)
{
	char **str;
	int l;
	char err;
	finput(str, file, l, err);

	if(err)
	{
		throw BCI();
	}

	if(l == 1)
	{
		StrToT(a, *str);
	}
	else
	{
		throw BSF();
	}
}

template <typename K, typename T>
void Input(Dict<K, T> &a)
{
	int count;
	Input(count);

	K keybuff;
	T valbuff;

	for(int i = 0; i < count; i++)
	{
		InputPair(keybuff, valbuff);
		a.Set(keybuff, valbuff);
	}
}

template <typename K, typename T>
void FInput(Dict<K, T> &a, FILE *file)
{
	int count;
	FInput(count, file);

	K keybuff;
	T valbuff;

	for(int i = 0; i < count; i++)
	{
		FInputPair(keybuff, valbuff, file);
		a.Set(keybuff, valbuff);
	}
}
