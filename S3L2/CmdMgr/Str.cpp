#pragma once

void copy(char *&target, char *source, char err = 0)					//нуль-терминатор не позже чем по индексу 254!
{																		//1 - слишком длинная исходная строка
	err = 0;
	unsigned char i = 0;
	char *ps = source;
	while(bool(*ps)*!bool(err))
	{
		if(i == 255)
		{
			throw BSF();
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

bool cmp(char *s1, char *s2)
{
	bool result = 1;
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
	return result;
}

void copy(char **&target, char **source, char err = 0)					//Не более 254 строк по 254 значимых символа
{																		//Конец массива должен быть nullptr (массив указателей на манер строк Си)
	err = 0;															//1 - слишком длинная строка
	unsigned char i = 0;												//2 - слишком много строк
	char **ps = source;
	while(bool(*ps)*!bool(err))
	{
		if(i == 255)
		{
			err = 2;
		}
		++i;
		++ps;
	}
	if(!err)
	{
		target = (char**)malloc(sizeof(char*)*i+1);
		char **pt = target;
		ps = source;
		while((!err)*bool(*ps))
		{
			copy(*pt, *ps, err);
			++pt;
			++ps;
		}
		*pt = 0;
	}
}

bool cmp(char **p1, char **p2)											//Сравнение массивов строк
{																		//Конец массива должен быть nullptr (массив указателей на манер строк Си)
	char **t1 = p1;
	char **t2 = p2;
	bool result = 1;
	bool run = 1;
	while((result)*(run))
	{
		if(!(bool(*p1)+bool(*p2)))										//Массивы закончились
		{
			run = 0;
		}
		else if (bool(*p1)*bool(*p2))									//Не закончились
		{
			result = cmp(*p1, *p2);
		}
		else															//Закончился один из двух
		{
			result = 0;
		}
		++p1;
		++p2;
	}
	return result;
}

void set(char **&target, unsigned char l)
{
	target = (char**)malloc(sizeof(char*)*((unsigned int)l+1));
	target[l] = 0;
}
