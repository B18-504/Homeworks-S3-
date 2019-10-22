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
