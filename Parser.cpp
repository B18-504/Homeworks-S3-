struct word
{
	char body[254];
	unsigned char l;
	word *next;
};

void wipe(word &a)
{
	a.next = 0;
}

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
		wipe(*c);
		free(c);
		c = next;
	}
	a.first = 0;
	a.l = 0;
}

void input(word &a, char &flag)
{
	flag = 3;
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
		}
		else if(buff == '\n')
		{
			flag = 1;
		}
		else if(a.l == 254)
		{
			flag = 2;
		}
		else
		{
			*ptr = buff;
			a.l++;
			buff = getchar();
		}
	}
}

void input(wordlist &a, char &err)
{
	word *ptr = (word*)malloc(sizeof(word));
	a.first = ptr;
	input(*ptr, err);
	a.l = 1;
	while (!err)
	{
		++a.l;
		ptr->next = (word*)malloc(sizeof(word));
		ptr = ptr->next;
		input(*ptr, err);
	}
	if (err == 2)
	{
		wipe(a);
	}
	--err;
}

void copy(wordlist &source, char **&target, char &err)
{
	err = 0;
	target = (char**)malloc(sizeof(char**)*source.l);
	word *wptr = source.first;
	char **cptr = target;
	while((ptr)*(!err))
	{
		*cptr = (char*)malloc(wptr->l);
		copy(*cptr, wptr->body);
		++cptr;
		wptr = wptr->next;
	}
}
