#pragma once

struct itdata
{
	char *vtname;
	void *(*generator)();
};

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
	bool strong;
};

struct HTable
{
	binding *(table[256]);
};

void reset(binding &a)
{
	free(a.ptr);
	free(a.type);
}


void init(HTable &table);

void bind(HTable &table, void *ref, char *key, char *type, bool strong = 1)				//Ключ и имя типа не более 254 символов!
{
	char *p = key;
	unsigned char i = 0;
	while(*p)
	{
		if(i == 255)
		{
			throw BSF();
		}
		++p;
		++i;
	}
	p = type;
	i = 0;
	while(*p)
	{
		if(i == 255)
		{
			throw BSF();
		}
		++p;
		++i;
	}

	unsigned char n = hash(key);
	binding *c = table.table[n], *last = 0;
	while(c)
	{
		if(cmp(key, c->key))
		{
			if(c->strong)
			{
				throw SNR();
			}
			else
			{
				reset(*c);

				c->ptr = ref;
				copy(c->key, key);
				copy(c->type, type);
				c->strong = strong;

				return;
			}
		}
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
	copy(last->key, key);
	copy(last->type, type);
	last->strong = strong;
}


void bindt(HTable &table, char *name, unsigned int size)
{
	unsigned int *a = (unsigned int*)malloc(sizeof(unsigned int));
	*a = size;
	bind(table, a, name, "t");
}

void bindvt(HTable &table, char *name, char &err)						//отдельная политика для полиморфных
{																		//позволяет производить инициализацию
	unsigned int *a = (unsigned int*)malloc(sizeof(unsigned int));		//посредством вызова create с передачей имплементирующего типа
	*a = 0;
	bind(table, a, name, "vt");
}

template <typename T>
void bindit(HTable &table, char *name, char *vtname, T *generator(), char &err)		//1 - слишком длинные имена типов
{																					//2 - не объявлен виртуальный тип
	binding *bvt;																	//3 - указанное имя виртуального типа занято не виртулаьным типом
	find(table, bvt, vtname, err);
	if(!err)
	{
		if(cmp(bvt->type, "vt"))
		{
			itdata *a = (itdata*)malloc(sizeof(itdata));
			copy(a->vtname, vtname, err);
			a->generator = generator;
			bind(table, a, name, "it");
		}
		else
		{
			err = 3;
		}
	}
}

void find(HTable &table, binding *&ptr, char *key, char &err)			//1 - слишком длинный ключ
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
		unsigned int h = hash(key);
		ptr = table.table[h];
		while((bool(ptr))*(bool(err)))
		{
			if(cmp(key, ptr->key))
			{
				err = 0;
				return;
			}
			ptr = ptr->next;
		}
	}
	ptr = 0;
	return;
}
