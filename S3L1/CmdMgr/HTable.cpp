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
};

struct HTable
{
	binding *(table[256]);
};


void init(HTable &table);

void bind(HTable &table, void *ref, char *key, char *type, char &err)	//Ключ и имя типа не более 254 символов!
{																		//1 - слишком длинный ключ/имя типа
	err = 0;															//2 - ключ занят
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
			cmp(key, c->key, *(bool*)&err);
			if(err)
			{
				err = 2;
				return;
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
		copy(last->key, key, err);
		copy(last->type, type, err);
	}
}

void bindt(HTable &table, char *name, unsigned int size, char &err)		//1 - слишком длиное имя нового типа
{																		//2 - ключ занят
	unsigned int *a = (unsigned int*)malloc(sizeof(unsigned int));
	*a = size;
	bind(table, a, name, "t", err);
}

void bindvt(HTable &table, char *name, char &err)						//отдельная политика для полиморфных
{																		//позволяет производить инициализацию
	unsigned int *a = (unsigned int*)malloc(sizeof(unsigned int));		//посредством вызова create с передачей имплементирующего типа
	*a = 0;
	bind(table, a, name, "vt", err);
}

template <typename T>
void bindit(HTable &table, char *name, char *vtname, T *generator(), char &err)		//1 - слишком длинные имена типов
{																					//2 - не объявлен виртуальный тип
	binding *bvt;																	//3 - указанное имя виртуального типа занято не виртулаьным типом
	find(table, bvt, vtname, err);
	if(!err)
	{
		bool b;
		cmp(bvt->type, "vt", b);
		if(b)
		{
			itdata *a = (itdata*)malloc(sizeof(itdata));
			copy(a->vtname, vtname, err);
			a->generator = generator;
			bind(table, a, name, "it", err);
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
		bool b;
		unsigned int h = hash(key);
		ptr = table.table[h];
		while((bool(ptr))*(bool(err)))
		{
			cmp(key, ptr->key, b);
			if(b)
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
