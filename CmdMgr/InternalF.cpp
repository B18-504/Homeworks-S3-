#pragma once

void create(binding **&argv, unsigned char argc)
{
	char err;
	bool b;
	if(argc == 3)
	{
		cmp((*(argv+1))->type, "t", b);
		if(b)
		{
			cmp((*(argv+2))->type, "input", b);
			if(b)
			{
				bind(*(HTable*)((*argv)->ptr), malloc(*(unsigned int*)((*(argv+1))->ptr)), (*(argv+2))->ptr, (*(argv+1))->key, err);
				if(err)
				{
					printf("Облажались, переменная не создана!\n");
				}
			}
		}
		else
		{
			cmp((*(argv+1))->type, "it", b);
			if(b)
			{
				cmp((*(argv+2))->type, "input", b);
				if(b)
				{
					bind(*(HTable*)((*argv)->ptr), ((itdata*)((*(argv+1))->ptr))->generator(), (*(argv+2))->ptr, ((itdata*)((*(argv+1))->ptr))->vtname, err);
					if(err)
					{
						printf("Облажались, переменная не создана!\n");
					}
				}
			}
			else
			{
				throw(ITN());
			}
		}
	}
	return;
}

void init(HTable &table)
{
	for(int i = 0; i < 256; i++)
	{
		table.table[i] = 0;
	}
	char err;															//На этом этапе ошибка = баг ОС/железа
	bind(table, &create, "create", "ft", err);
}
