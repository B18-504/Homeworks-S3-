#pragma once

#include <chrono>

void getcmd(HTable &table, bool &finish, FILE *script_file = 0)
{	
	char **p;
	unsigned char argc;
	char err;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	
	
	if(script_file)
	{
		finput(p, script_file, argc, err);
	}
	else
	{
		printf("--> ");
		input(p, argc, err);
	}
	
	
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
		finish = cmp(*p, "exit");
		if(finish)
		{
			return;
		}

		bool time_submission = cmp(*p, "-t");
		if(time_submission)
		{
			++p;
			if(argc != 1)
			{
				--argc;
			}
			else
			{
				printf("Executing empty call time submission\n");
				start = std::chrono::system_clock::now();
				end = std::chrono::system_clock::now();
				int msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
				printf("%u\n", msec);
				--p;
				free(p);
				return;
			}
		}
		
		
		binding *function;
		find(table, function, *p, err);
		if(err)
		{
			printf("function \"%s\" not found\n", *p);
			return;
		}		
		if(!cmp(function->type, "f"))
		{
			if(!cmp(function->type, "ft"))
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
				if(time_submission)
				{
					start = std::chrono::system_clock::now();
					f(argv, argc);
					end = std::chrono::system_clock::now();
					int msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
					printf("%u\n", msec);
				}
				else
				{
					f(argv, argc);
				}
				
				
				c = argv;
				free((*c)->type);
				(*c)->ptr = 0;
				free(*c);
				++c;
				for(unsigned char i = 0; i < (argc - 1); i++)
				{
					if(cmp((*c)->type, "input"))
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
				if(time_submission)
				{
					start = std::chrono::system_clock::now();
					f(argv);
					end = std::chrono::system_clock::now();
					int msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
					printf("%u\n", msec);
				}
				else
				{
					f(argv);
				}
			}
			else
			{
				printf("?\n");
			}
			
		}
		if(time_submission)
		{
			--p;
		}
		//free(p);
	}
}
