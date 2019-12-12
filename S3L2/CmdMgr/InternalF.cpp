#pragma once

extern void getcmd(HTable&, bool&, FILE*);

void create(binding **&argv, unsigned char argc)
{
	char err;
	if(argc == 3)
	{
		if(cmp(argv[1]->type, "t"))
		{
			if(cmp(argv[2]->type, "input"))
			{
				bind(*(HTable*)(argv[0]->ptr), 0, argv[2]->ptr, argv[1]->key, 0);
				if(err)
				{
					printf("Облажались, переменная не создана!\n");
				}
			}
			else if(!argv[2]->strong)
			{
				reset(*(argv[2]));

				argv[2]->ptr = 0;
				copy(argv[2]->type, argv[1]->key, err);
			}
			else
			{
				throw SNR();
			}
		}
		else if(cmp(argv[1]->type, "it"))
		{
			if(cmp(argv[2]->type, "input"))
			{
				bind(*(HTable*)(argv[0]->ptr), ((itdata*)(argv[1]->ptr))->generator(), argv[2]->ptr, ((itdata*)(argv[1]->ptr))->vtname, 0);
				if(err)
				{
					printf("Облажались, переменная не создана!\n");
				}
			}
			else if(!argv[2]->strong)
			{
				reset(*(argv[2]));

				argv[2]->ptr = ((itdata*)(argv[1]->ptr))->generator();
				copy(argv[2]->type, ((itdata*)(argv[1]->ptr))->vtname, err);
			}
			else
			{
				throw SNR();
			}
		}
		else if(cmp(argv[1]->type, "vt"))
		{
			if(cmp(argv[2]->type, "input"))
			{
				bind(*(HTable*)(argv[0]->ptr), 0, argv[2]->ptr, argv[1]->key, 0);
				if(err)
				{
					printf("Облажались, переменная не создана!\n");
				}
			}
			else if(!argv[2]->strong)
			{
				reset(*(argv[2]));

				argv[2]->ptr = 0;
				copy(argv[2]->type, argv[1]->key);
			}
			else
			{
				throw SNR();
			}
		}
		else
		{
			throw(ITN());
		}
	}
	return;
}

void exec(binding **&argv, unsigned char argc)
{
	char err;
	if(argc == 2)
	{
		if(cmp(argv[1]->type, "input"))
		{
			FILE *script_file = fopen(argv[1]->ptr, "r");
			if(script_file)
			{
				bool finish = 0;
				while(!finish)
				{
					getcmd(*(HTable*)(argv[0]->ptr), finish, script_file);
				}
				fclose(script_file);
			}
			else
			{
				throw FSE();
			}
		}
	}
}

void init(HTable &table)
{
	for(int i = 0; i < 256; i++)
	{
		table.table[i] = 0;
	}
	char err;															//На этом этапе ошибка = баг ОС/железа
	bind(table, &create, "create", "ft", err);
	bind(table, &exec, "exec", "ft", err);
}
