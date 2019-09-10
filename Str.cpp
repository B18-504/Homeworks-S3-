void copy(char *&target, char *source, char &err)						//нуль-терминатор не позже чем по индексу 254!
{																		//1 - слишком длинная исходная строка
	err = 0;
	unsigned char i = 0;
	char *ps = source;
	while((*ps)*(!err))
	{
		if(i == 255)
		{
			err = 1;
		}
		++ps;
		++i;
	}
	if(!err)
	{
		target = (char*)malloc(i+1);
		char *pt = target;
		ps = source;
		for(unsigned int j = 0; j < i; j++)
		{
			*pt = *ps;
			++pt;
			++ps;
		}
		*pt = 0;
	}
}

void cmp(char *s1, char *s2, bool &result)								//1 - одинаковые
{
	result = 1;
	bool run = 1;
	while((result)*(run))
	{
		if(*s1 != *s2)
		{
			result = 0;
		}
		else if(!*s1)
		{
			run = 0;
		}
		++s1;
		++s2;
	}
}
