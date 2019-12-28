#pragma once

bool isdigit(char c)
{
	return ((c > 47) * (c < 58));
}

void Print(int a)
{
	printf("%d", a);
}

void FPrint(int a, FILE *file)
{
	fprintf(file, "%d", a);
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

void Print(Route &r)
{
	for(int i = 0; i < (r.nodes_count - 1); i++)
	{
		printf("%d: %d -> %d\n", r.nodes_ids[i], r.connections_ids[i], r.nodes_ids[i+1]);
	}

	printf("\nETA is %d\n", r.ETA);
}

void Input(TransportGraph &g)
{
	printf("number of nodes: ");
	Input(g.nodes_count);
	g.nodes_array = new TransportGraph::TransportNode[g.nodes_count];

	int count;
	printf("number of connections: ");
	Input(count);


	int from_id, to_id, interval, duration, offset;
	for(int i = 0; i < count; i++)
	{
		printf("connection goes from: ");
		Input(from_id);

		printf("to: ");
		Input(to_id);

		printf("route interval: ");
		Input(interval);

		printf("trip duration: ");
		Input(duration);

		printf("offset: ");
		Input(offset);

		g.AddConnection(from_id, to_id, interval, duration, offset);
	}
}
