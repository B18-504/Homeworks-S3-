void getcmd(HTable &table, bool &finish)
{
	printf("--> ");
	
	char **p;
	unsigned char argc;
	char err;
	
	
	input(p, argc, err);
	
	if(err == 1)
	{
		printf("too long word\n");
		return;
	}
	else if(err == 2)
	{
		printf("too much words\n");
		return;
	}
	
	
	if(argc)
	{
		cmp(*p, "exit", finish);
		if(finish)
		{
			return;
		}
		
		
		binding *function;
		find(table, function, *p, err);
		if(err)
		{
			printf("function \"%s\" not found\n", *p);
			return;
		}		
		bool b;
		cmp(function->type, "f", b);
		if(!b)
		{
			cmp(function->type, "ft", b);
			if(!b)
			{
				printf("function \"%s\" not found\n", *p);
				return;
			}
			else
			{
				++p;
				binding **argv = (binding**)malloc(argc*sizeof(binding*));
				binding **c = argv;
				char err;
				*c = (binding*)malloc(sizeof(binding));
				(*c)->ptr = &table;
				copy((*c)->key, "", err);
				copy((*c)->type, "HTable", err);
				(*c)->next = 0;
				++c;
				for(unsigned char i = 0; i < (argc - 1); i++)
				{
					find(table, *c, *p, err);
					if(err)
					{
						char *ptr;
						*c = (binding*)malloc(sizeof(binding));
						(*c)->next = 0;
						copy((*c)->key, "", err);
						copy((*c)->type, "input", err);
						copy(ptr, *p, err);
						(*c)->ptr = (void*)ptr;
						ptr = 0;
					}
					++c;
					++p;
				}
				
				void (*f)(binding **&, unsigned char) = function->ptr;
				f(argv, argc);
				
				c = argv;
				free((*c)->type);
				(*c)->ptr = 0;
				free(*c);
				++c;
				for(unsigned char i = 0; i < (argc - 1); i++)
				{
					cmp((*c)->type, "input", b);
					if(b)
					{
						free((*c)->type);
						free((*c)->ptr);
						free(*c);
					}
					++c;
				}
			}
		}

		else
		{
			++p;
			--argc;
			binding *c;
			void ***argv = (void***)malloc(argc*sizeof(void**));
			void ***a = argv;
			char **types = (char**)malloc((argc+1)*sizeof(char*));
			char **t = types;
			char err;
			for(unsigned char i = 0; i < argc; i++)
			{
				find(table, c, *p, err);
				if(err)
				{
					*a = (void**)malloc(sizeof(void*));
					copy(**(char***)(a), *p, err);
					copy(*t, "input", err);								//Тип input предполагается для передачи параметров команд
				}
				else
				{
					*a = &(c->ptr);
					copy(*t, c->type, err);
				}
				++p;
				++a;
				++t;
			}
			*t = 0;
			
			void (*f)(void***);
			
			find(*(Overrides*)(function->ptr), f, types, err);
			if(!err)
			{
				f(argv);
			}
			else
			{
				printf("?\n");
			}
			
		}
	}
	return;
}
