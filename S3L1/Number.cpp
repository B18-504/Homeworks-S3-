#pragma once

Int::Int(int a)
{
	body = a;
}

void Int::SetRandVal()
{
	body = rand();
}

double Int::ValueAsDbl()
{
	return double(body);
}

int Int::ValueAsInt()
{
	return body;
}

uint Int::ValueAsUint()
{
	return uint(body);
}

char *(Int::ValueAsStr)()
{
	char *buff = malloc(50);
	sprintf(buff, "%d", body);
	return buff;
}

Number *(Int::Clone)()
{
	return new Int(body);
}





	

Uint::Uint(uint a)
{
	body = a;
}

void Uint::SetRandVal()
{
	body = rand();
}

double Uint::ValueAsDbl()
{
	return double(body);
}

int Uint::ValueAsInt()
{
	return int(body);
}

uint Uint::ValueAsUint()
{
	return body;
}

char *(Uint::ValueAsStr)()
{
	char *buff = malloc(50);
	sprintf(buff, "%u", body);
	return buff;
}

Number *(Uint::Clone)()
{
	return new Uint(body);
}








Double::Double(double a)
{
	body = a;
}

void Double::SetRandVal()
{
	body = rand();
}

double Double::ValueAsDbl()
{
	return double(body);
}

int Double::ValueAsInt()
{
	return int(body);
}

uint Double::ValueAsUint()
{
	return uint(body);
}

char *(Double::ValueAsStr)()
{
	char *buff = malloc(50);
	sprintf(buff, "%lf", body);
	return buff;
}

Number *(Double::Clone)()
{
	return new Double(body);
}








Bool::Bool(bool a)
{
	body = a;
}

void Bool::SetRandVal()
{
	body = rand();
}

double Bool::ValueAsDbl()
{
	return double(body);
}

int Bool::ValueAsInt()
{
	return int(body);
}

uint Bool::ValueAsUint()
{
	return uint(body);
}

char *(Bool::ValueAsStr)()
{
	if(body)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

Number *(Bool::Clone)()
{
	return new Bool(body);
}


Number *RandInt()
{
	return new Int(rand());
}








bool operator==(Number &a, Number &b)
{
	return(a.ValueAsDbl() == b.ValueAsDbl());
}

bool operator>(Number &a, Number &b)
{
	return(a.ValueAsDbl() > b.ValueAsDbl());
}

template <typename T>
char LessOrEquals(Number &a, Number &b)
{
	if(((T*)(&a))->body < ((T*)(&b))->body)
	{
		return 1;
	}
	else if(((T*)(&a))->body > ((T*)(&b))->body)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

template <typename T>
char GreatOrEquals(Number &a, Number &b)
{
	if(((T*)(&a))->body > ((T*)(&b))->body)
	{
		return 1;
	}
	else if(((T*)(&a))->body < ((T*)(&b))->body)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

void dummyF()
{
	GreatOrEquals<Int>(*RandInt(), *RandInt());
}
