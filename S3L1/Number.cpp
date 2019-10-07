#pragma once

Int::Int(int a)
{
	body = a;
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








bool operator==(Number &a, Number &b)
{
	return(a.ValueAsDbl() == b.ValueAsDbl());
}

bool operator>(Number &a, Number &b)
{
	return(a.ValueAsDbl() > b.ValueAsDbl());
}
