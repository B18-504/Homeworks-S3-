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

Number *RandDouble()
{
	Double *tmp = new Double;
	tmp->body = rand();
	tmp->body *= rand();
	tmp->body /= rand();
	return tmp;
}






bool operator==(Number &a, Number &b)											//DO NOT USE AS COMPARISON FOR SORTS (see sorts.h)
{
	return(a.ValueAsDbl() == b.ValueAsDbl());
}

bool operator>(Number &a, Number &b)											//DO NOT USE AS COMPARISON FOR SORTS
{
	return(a.ValueAsDbl() > b.ValueAsDbl());
}

template <typename T>															//To be used as comparison parameters, returns 1, if Less/Greater, -1 if Equal, 0 if neither
char LessOrEquals(Number &a, Number &b)
{
	if(((T&)a).body < ((T&)b).body)
	{
		return 1;
	}
	else if(((T&)a).body > ((T&)b).body)
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
	if(((T&)a).body > ((T&)b).body)
	{
		return 1;
	}
	else if(((T&)a).body < ((T&)b).body)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}