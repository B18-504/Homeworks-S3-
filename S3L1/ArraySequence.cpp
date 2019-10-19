#pragma once

template <typename T>
void ArraySequence<T>::extend()
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
		T **old = body;
		body = (T**)realloc(body, allocated_bytes);
		if(old != body)
		{
			Sequence<T>::SList.Unbind();
		}
	}
	if(body == 0)
	{
		throw(MAE());
	}
}

template <typename T>
T *(ArraySequence<T>::operator[])(uint index) const
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
T *(ArraySequence<T>::GetFirst)() const
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
T *(ArraySequence<T>::GetLast)() const
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
void ArraySequence<T>::Append(T *value)
{
	ulint l = Sequence<T>::len;
	++l;
	l *= sizeof(T*);
	while(l > allocated_bytes)
	{
		extend();
	}
	body[(Sequence<T>::len++)] = value->Clone();
}

template <typename T>
void ArraySequence<T>::Prepend(T *value)
{
	ulint l = Sequence<T>::len;
	++l;
	l *= sizeof(T*);
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
void ArraySequence<T>::Insert(T *value, uint index)
{
	if(index > Sequence<T>::len)
	{
		throw(OoR());
	}
	ulint l = Sequence<T>::len;
	++l;
	l *= sizeof(T*);
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
void ArraySequence<T>::Remove(T *value)
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
void ArraySequence<T>::Clear()
{
	free(body);
	body = 0;
	allocated_bytes = 0;
	Sequence<T>::len = 0;
}

template <typename T>
Sequence<T> *(ArraySequence<T>::GetSubS)(uint start, uint end) const
{
	if(end < Sequence<T>::len)
	{
		ArraySequence<T> *result = new ArraySequence<T>;
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

template <typename T>
void ArraySequence<T>::SetFromStr(char **values, uint length)
{
	free(body);
	allocated_bytes = 0;
	Sequence<T>::len = 0;
	
	while(allocated_bytes < length*sizeof(T*))
	{
		extend();
	}
	Sequence<T>::len = length;
	
	T **tmp = body;
	
	for(uint i = 0; i < length; i++)
	{
		*(tmp++) = StrToNumber(*(values++));
	}
}

template <typename T>
void ArraySequence<T>::SetRandVals(T *(*generator)(), uint length)
{
	free(body);
	allocated_bytes = 0;
	Sequence<T>::len = 0;
	
	while(allocated_bytes < length*sizeof(T*))
	{
		extend();
	}
	Sequence<T>::len = length;
	
	T **tmp = body;
	
	for(uint i = 0; i < length; i++)
	{
		*(tmp++) = generator();
	}
}

template <typename T>
typename Sequence<T>::Slider &(ArraySequence<T>::InitSlider)(uint initpos) const
{
	if(initpos < Sequence<T>::len)
	{
		typename Sequence<T>::Slider *tmp = new (typename Sequence<T>::Slider)(this, (body + initpos), initpos);
		Sequence<T>::SList.Append(tmp);
		return(*(Sequence<T>::SList.last->body));
	}
	else
	{
		return *new typename Sequence<T>::Slider();
	}
}

template <typename T>
void ArraySequence<T>::ShiftPtrRight(void  *&ptr, uint &position) const
{
	if(((position + 1) < Sequence<T>::len) * (position != -1u))
	{
		ptr += sizeof(T*);
		++position;
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
void ArraySequence<T>::ShiftPtrLeft(void  *&ptr, uint &position) const
{
	if(position != 0)
	{
		ptr -= sizeof(T*);
		--position;
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
T *(ArraySequence<T>::GetVal)(void *ptr) const
{
	return *(T**)ptr;
}

template <typename T>
void ArraySequence<T>::SetVal(T *val, void *ptr) const
{
	*((T**)ptr) = val;
}

template <typename T>
ArraySequence<T>::~ArraySequence()
{
	free(body);
}
