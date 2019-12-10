#pragma once



//Консольный ввод

//long wordlists unsafe



struct word
{
	char body[254];
	unsigned char l;
	word *next;
};

struct wordlist
{
	word *first;
	int l;
};

void wipe(wordlist &a)
{
	word *c = a.first, *next;
	while(c)
	{
		next = c->next;
		c->next = 0;
		free(c);
		c = next;
	}
	a.first = 0;
	a.l = 0;
}

void input(word &a, char &flag)											//0 - успешный ввод слова
{																		//1 - успешный ввод последнего слова
	flag = 3;															//2 - слишком длинное слово
	a.l = 0;
	a.next = 0;
	char buff;
	char *ptr = a.body;
	buff = getchar();
	while (flag == 3)
	{
		if (buff == ' ')
		{
			flag = 0;
			*ptr = 0;
		}
		else if(buff == '\n')
		{
			flag = 1;
			*ptr = 0;
		}
		else if(a.l == 254)
		{
			flag = 2;
			*ptr = 0;
		}
		else
		{
			*(ptr++) = buff;
			a.l++;
			buff = getchar();
		}
	}
}

void input(wordlist &a, char &err)										//1 - слишком длинное слово
{																		//2 - слишком много слов
	word *ptr = (word*)malloc(sizeof(word));
	a.first = ptr;
	a.l = 0;
	err = 0;
	while (!err)
	{
		if (a.l == 255)
		{
			err = 3;
		}
		else
		{
			input(*ptr, err);
			if(ptr->l)
			{
				++a.l;
				if(!err)
				{
					ptr->next = (word*)malloc(sizeof(word));
					ptr = ptr->next;
				}
			}
			else
			{
				ptr->next = 0;
			}
		}
	}
	if (err > 1)
	{
		wipe(a);
	}
	--err;
}

void copy(char **&target, wordlist &source, char &err)
{
	err = 0;
	target = (char**)malloc(sizeof(char**)*source.l);
	word *wptr = source.first;
	char **cptr = target;
	while((bool(wptr))*(!err))
	{
		*cptr = (char*)malloc(wptr->l);
		copy(*cptr, wptr->body, err);
		++cptr;
		wptr = wptr->next;
	}
}

void input(char **&p, unsigned char &length, char &err)					//1 - слишком длинное слово
{																		//2 - слишком много слов
	wordlist a;
	input(a, err);
	length = a.l;
	if (!err)
	{
		copy(p, a, err);
	};
	wipe(a);
}



//Файловый ввод




void finput(word &a, FILE *fstream, char &flag)							//0 - успешный ввод слова
{																		//1 - успешный ввод последнего в строке слова
	flag = 4;															//2 - слишком длинное слово
	a.l = 0;															//3 - успешный ввод последнего в файле слова
	a.next = 0;
	int buff;															
	char *ptr = a.body;
	buff = fgetc(fstream);
	while (flag == 4)
	{
		if (buff == ' ')
		{
			flag = 0;
			*ptr = 0;
		}
		else if(buff == '\n')
		{
			flag = 1;
			*ptr = 0;
		}
		else if(a.l == 254)
		{
			flag = 2;
			*ptr = 0;
		}
		else if(buff == EOF)
		{
			flag = 3;
			*ptr = 0;
		}
		else
		{
			*(ptr++) = buff;
			a.l++;
			buff = fgetc(fstream);
		}
	}														
}

void finput(wordlist &a, FILE *fstream, char &err)						//1 - слишком длинное слово
{																		//2 - успешный ввод последнего в файле слова
	word *ptr = (word*)malloc(sizeof(word));
	a.first = ptr;
	a.l = 0;
	err = 0;
	while (!err)
	{
		/*if (a.l == 255)
		{
			err = 4;
		}*/
		//else
		finput(*ptr, fstream, err);
		if(ptr->l)
		{
			++a.l;
			if(!err)
			{
				ptr->next = (word*)malloc(sizeof(word));
				ptr = ptr->next;
			}
		}
		else
		{
			ptr->next = 0;
		}
	}
	if (err == 2)
	{
		wipe(a);
	}
	--err;
}

void finput(char **&p, FILE *fstream, unsigned char &length, char &err)	//1 - слишком длинное слово
{																		//2 - файл закончился
	if(!bool(fstream))													//3 - слишком много слов
	{
		throw FSE();
	}
	wordlist a;
	finput(a, fstream, err);
	length = a.l;
	if (!err)
	{
		copy(p, a, err);
	};
	wipe(a);
}

void finput(char **&p, FILE *fstream, int &length, char &err)	//1 - слишком длинное слово
{																//2 - файл закончился
	if(!bool(fstream))											//3 - слишком много слов
	{
		throw FSE();
	}
	wordlist a;
	finput(a, fstream, err);
	length = a.l;
	if (err != 1)
	{
		copy(p, a, err);
	}
	wipe(a);
}