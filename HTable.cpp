unsigned char hash(char *s)
{
	unsigned char h = 0;
	while (*s)
	{
		h += *(unsigned char*)s;
		++s;
	}
	return h;
}

struct binding
{
	void *ptr;
	char *key;
	binding *next;
	char *type;
};

struct HTable
{
	binding *(table[256]);
};


void init(HTable &table)
{
	for(int i = 0; i < 256; i++)
	{
		table.table[i] = 0;
	}
}

void bind(HTable &table, void *ref, char *key, char *type, char &err)	//Ключ и имя типа не более 254 символов!
{																		//1 - слишком длинный ключ/имя типа
	err = 0;
	char *p = key;
	unsigned char i = 0;
	while((*p)*(!err))
	{
		if(i == 255)
		{
			err = 1;
		}
		++p;
		++i;
	}
	p = type;
	i = 0;
	while((*p)*(!err))
	{
		if(i == 255)
		{
			err = 1;
		}
		++p;
		++i;
	}
	if(!err)
	{
		unsigned char n = hash(key);
		binding *c = table.table[n], *last = 0;
		while(c)
		{
			last = c;
			c = c->next;
		}
		if(last)
		{
			last->next = (binding*)malloc(sizeof(binding));
			last = last->next;
		}
		else
		{
			table.table[n] = (binding*)malloc(sizeof(binding));
			last = table.table[n];
		}
		last->next = 0;
		last->ptr = ref;
		copy(last->key, key, err);
		copy(last->type, type, err);
	}
}

binding *find(HTable &table, char *key, char &err)						//1 - слишком длинный ключ
{																		//2 - ключ не найден
	err = 0;
	char *p = key;
	unsigned int i = 0;
	while((*p)*(!err))
	{
		if(i == 255)
		{
			err = 1;
		}
		++p;
		++i;
	}
	if(!err)
	{
		err = 2;
		bool b;
		unsigned int h = hash(key);
		binding *c = table.table[h];
		while((bool(c))*(bool(err)))
		{
			cmp(key, c->key, b);
			if(b)
			{
				err = 0;
				return c;
			}
			c = c->next;
		}
	}
	return 0;
}
