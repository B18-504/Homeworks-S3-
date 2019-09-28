void inputi(void **argv)
{
	scanf("%d", (int*)(*argv));
	FLUSH;
}

void inputui(void **argv)
{
	scanf("%u", (uint*)(*argv));
	FLUSH;
}

void inputd(void **argv)
{
	scanf("%lf",(double*)(*argv));
	FLUSH;
}

void printi(void **argv)
{
	printf("%d\n", *(int*)(*argv));
}

void printui(void **argv)
{
	printf("%u", *(uint*)(*argv));
}

void printd(void **argv)
{
	printf("%lf\n", *(double*)(*argv));
}

void binds(HTable &table)
{
	char err;
	
	bindt(table, "int", sizeof(int), err);
	bindt(table, "uint", sizeof(uint), err);
	bindt(table, "double", sizeof(double), err);
	bindt(table, "ArrSeqInt", sizeof(Array<int>), err);
	
	char **types;
	set(types, 1, err);
	
	
	copy(types[0], "int", err);
	bindf(table, inputi, "input", types, err);
	bindf(table, printi, "print", types, err);
	
	copy(types[0], "uint", err);
	bindf(table, inputui, "input", types, err);
	bindf(table, printui, "print", types, err);
	
	copy(types[0], "double", err);
	bindf(table, inputd, "input", types, err);
	bindf(table, printd, "print", types, err);
}
