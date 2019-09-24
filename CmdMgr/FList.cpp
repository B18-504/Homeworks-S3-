struct Override 
{
	Override *next;
	void *ptr;
	char **types;
};

struct Overrides
{
	Override *head;
};

void find(Overrides &o, void (*&function)(void**), char **types, char &err)	//1 - нет нужной перегрузки
{
	Override *ov = o.head, *op;
	err = 1;
	bool b;
	while(bool(err)*bool(ov))
	{
		cmp(types, ov->types, b);
		err = !b;
		op = ov;
		ov = ov->next;
	}
	if(err)
	{
		function = 0;
	}
	else
	{
		function = op->ptr;
	}
	return;
}

void bindf(HTable &table, void *function, char *key, char **types, char &err)	//1 - слишком длинное имя/типы
{																		//2 - имя занято переменной или внутренней функцией (пока что нельзя перегружать внутренние обычными)
	binding *pb;
	find(table, pb, key, err);
	bool b;
	Override *po;
	if(err == 2)
	{
		po = (Override*)malloc(sizeof(Overrides));						//грязный хак - у Overrides и Override указатель на следующий по смещению 0
		po->next = 0;
		err = 0;
		bind(table, po, key, "f", err);
	}
	else if(err == 1)
	{
		return;
	}
	else
	{
		cmp(pb->type, "f", b);
		if(b)
		{
			po = pb->ptr;
		}
		else
		{
			err = 2;
			return;
		}
	}
	while(po->next)														
	{
		po = po->next;
	}
	po->next = (Override*)malloc(sizeof(Override));
	po = po->next;
	po->next = 0;
	po->ptr = function;
	copy(po->types, types, err);
	return;
}
