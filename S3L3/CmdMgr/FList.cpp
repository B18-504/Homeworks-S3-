#pragma once

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

void find(Overrides &o, void (*&function)(void***), char **types, char &err)	//1 - нет нужной перегрузки
{
	Override *ov = o.head, *op;
	err = 1;
	while(bool(err)*bool(ov))
	{
		err = !cmp(types, ov->types);
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

void bindf(HTable &table, void(*function)(void***), char *key, char **types, char &err)	//1 - слишком длинное имя/типы
{																		//2 - имя занято переменной или внутренней функцией (пока что нельзя перегружать внутренние обычными)
	binding *pb;														//3 - перегрузка с данными типами уже существует
	find(table, pb, key, err);
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
		if(cmp(pb->type, "f"))
		{
			po = pb->ptr;
		}
		else
		{
			err = 2;
			return;
		}
	}
	while((bool(po->next))*(!err))														
	{
		po = po->next;
		if(cmp(po->types, types))
		{
			err = 3;
			return;
		}
	}
	po->next = (Override*)malloc(sizeof(Override));
	po = po->next;
	po->next = 0;
	po->ptr = function;
	copy(po->types, types, err);
	return;
}
