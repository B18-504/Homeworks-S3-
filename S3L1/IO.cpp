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
	uint uin = 0;
	bool bl;
	
	cmp(str, "true", b);
	if(b)
	{
		return new Bool(true);
	}
	
	cmp(str, "false", b);
	if(b)
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
		else if((!first) * (*str == 'u') * (*(str + 1) == 0))
		{
			return new Uint(in);
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
	uin = in;
	
	if((isdigit(*str)) * ((uin*10 + *str - 48) >= uin) * (*(str + 1) == 0) *(in > 0))
	{
		return new Uint(uin);
	}
	
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
