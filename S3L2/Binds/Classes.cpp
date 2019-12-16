#pragma once

Sequence<Number> *generateArray()
{
	return new ArraySequence<Number>;
}

Sequence<Number> *generateListSequence()
{
	return new ListSequence<Number>;
}
