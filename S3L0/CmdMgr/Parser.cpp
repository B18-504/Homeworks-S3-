struct word
{
	char body[254];
	unsigned char l;
	word *next;
};

struct wordlist
{
	word *first;
	unsigned char l;
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
	return;
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
	return;
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
	return;
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
	return;
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
	return;
}
