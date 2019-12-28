void StartInFile(void ***argv)
{
	(*(argv[0])) = fopen((char*)(*(argv[1])), "r");
	if(!bool(*(argv[0])))
	{
		throw FSE();
	}
}

void StartOutFile(void ***argv)
{
	(*(argv[0])) = fopen((char*)(*(argv[1])), "w");
	if(!bool(*(argv[0])))
	{
		throw FSE();
	}
}

void StopFile(void ***argv)
{
	if(bool(*(argv[0])))
	{
		fclose(*(argv[0]));
		*(argv[0]) = 0;
	}
}