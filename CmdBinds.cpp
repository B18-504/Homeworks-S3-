void *f1(void *b)
{
	int *a = (int*)malloc(sizeof(int));
	*a = 1*(*(int*)b);
	return a;
}

void *f2(void *b)
{
	int *a = (int*)malloc(sizeof(int));
	*a = 2*(*(int*)b);
	return a;
}

class dummy
{
	public:
	void testmethod(int a)
	{
		printf("%d", a*5);
	}
};

void dummy_tst(dummy &a, int b)
{
	a.testmethod(b);
}
