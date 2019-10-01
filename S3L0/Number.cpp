Int::Int(int a)
{
	body = a;
}

void Int::input()
{
	scanf("%d", &body);
	FLUSH;
}

void Int::print()
{
	printf("%d\n", body);
}

double Int::ValueAsDbl()
{
	return double(body);
}

Number *(Int::Clone)()
{
	return new Int(body);
}
	

Uint::Uint(uint a)
{
	body = a;
}

void Uint::input()
{
	scanf("%u", &body);
	FLUSH;
}

void Uint::print()
{
	printf("%u\n", body);
}

double Uint::ValueAsDbl()
{
	return double(body);
}

Number *(Uint::Clone)()
{
	return new Uint(body);
}


Double::Double(double a)
{
	body = a;
}

void Double::input()
{
	scanf("%lf", &body);
	FLUSH;
}

void Double::print()
{
	printf("%lf\n", body);
}

double Double::ValueAsDbl()
{
	return double(body);
}

Number *(Double::Clone)()
{
	return new Double(body);
}


Bool::Bool(bool a)
{
	body = a;
}

void Bool::input()
{
	int a;
	scanf("%d", &a);
	FLUSH;
	body = bool(a);
}

void Bool::print()
{
	printf("%d\n", body);
}

double Bool::ValueAsDbl()
{
	return double(body);
}

Number *(Bool::Clone)()
{
	return new Bool(body);
}


bool operator==(Number &a, Number &b)
{
	return(a.ValueAsDbl() == b.ValueAsDbl());
}
