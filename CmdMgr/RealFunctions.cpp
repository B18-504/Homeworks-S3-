template <typename T>
void dup(T &a)
{
	a += a;
}

void input(int &a)
{
	scanf("%d", &a);
	getchar();
}

void input(double &a)
{
	scanf("%lf", &a);
	getchar();
}

void print(int a)
{
	printf("%d\n", a);
}

void print(double a)
{
	printf("%lf\n", a);
}
