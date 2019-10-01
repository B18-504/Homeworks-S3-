Number *generateInt()
{
	return new Int;
}

Number *generateUint()
{
	return new Uint;
}

Number *generateDouble()
{
	return new Double;
}

Number *generateBool()
{
	return new Bool;
}

Sequence<Number*> *generateArray()
{
	return new Array<Number*>;
}

Sequence<Number*> *generateList()
{
	return new List<Number*>;
}
