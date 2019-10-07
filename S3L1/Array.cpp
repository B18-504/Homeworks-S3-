#pragma once

template <typename T>
void Array<T>::extend()
{
	if (allocated_bytes == 0)
	{
		allocated_bytes = 8;
		body = (T**)malloc(8);
	}
	else if(allocated_bytes == -1u)
	{
		throw(MSR());
	}
	else if(allocated_bytes > (allocated_bytes + allocated_bytes))
	{
		allocated_bytes = -1u;
		body = (T**)realloc(body, -1u);
	}
	else
	{
		allocated_bytes += allocated_bytes;
		body = (T**)realloc(body, allocated_bytes);
	}
	if(body == 0)
	{
		throw(MAE());
	}
}

template <typename T>
T *(Array<T>::operator[])(uint index)
{
	if(index < Sequence<T>::len)
	{
		return body[index];
	}
	else
	{
		throw(OoR());
	}
}

template <typename T>
T *(Array<T>::GetFirst)()
{
	if(Sequence<T>::len)
	{
		return *body;
	}
	else
	{
		throw(CIE());
	}
}

template <typename T>
T *(Array<T>::GetLast)()
{
	if(Sequence<T>::len)
	{
		return body[Sequence<T>::len - 1];
	}
	else
	{
		throw(CIE());
	}
}

template <typename T>
void Array<T>::Append(T *value)
{
	ulint l = Sequence<T>::len;
	++l;
	l *= sizeof(T);
	while(l > allocated_bytes)
	{
		extend();
	}
	body[(Sequence<T>::len++)] = value->Clone();
}

template <typename T>
void Array<T>::Prepend(T *value)
{
	ulint l = Sequence<T>::len;
	++l;
	l *= sizeof(T);
	while(l > allocated_bytes)
	{
		extend();
	}
	for(uint i = Sequence<T>::len; i > 0; i--)
	{
		body[i] = body[i-1];
	}
	body[0] = value->Clone();
	++Sequence<T>::len;
}

template <typename T>
void Array<T>::Insert(T *value, uint index)
{
	if(index > Sequence<T>::len)
	{
		throw(OoR());
	}
	ulint l = Sequence<T>::len;
	++l;
	l *= sizeof(T);
	while(l > allocated_bytes)
	{
		extend();
	}
	uint i;
	for(i = Sequence<T>::len; i > index; i--)
	{
		body[i] = body[i - 1];
	}
	body[i] = value->Clone();
	++Sequence<T>::len;
}

template <typename T>
void Array<T>::Remove(T *value)
{
	uint i = 0;
	bool found = 0;
	while((i < Sequence<T>::len)*(!found))
	{
		if(*(body[i]) == *value)
		{
			found = 1;
		}
		else
		{
			++i;
		}
	}
	if(found)
	{
		++i;
		for(i; i < Sequence<T>::len; i++)
		{
			body[i-1] = body[i];
		}
		--Sequence<T>::len;
	}
}

template <typename T>
Sequence<T> *(Array<T>::GetSubS)(uint start, uint end)
{
	if(end < Sequence<T>::len)
	{
		Array<T> *result = new Array<T>;
		for(uint i = start; i <= end; i++)
		{
			result->Append(body[i]);
		}
		return result;
	}
	else
	{
		throw(OoR());
	}
}
