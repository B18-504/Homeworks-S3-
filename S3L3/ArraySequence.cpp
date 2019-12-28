#pragma once																	//would be nice to enhance behavior of extend when need to extend alloc'd memory multiple times

template <typename T>
void ArraySequence<T>::extend()
{
	if (allocated_bytes == 0)
	{
		allocated_bytes = 8;
		body = (T**)malloc(8);
	}
	else if(allocated_bytes == INT32_MAX)
	{
		throw MCE();
	}
	else if(allocated_bytes > (allocated_bytes + allocated_bytes))
	{
		allocated_bytes = INT32_MAX;
		T **old = body;
		body = (T**)realloc(body, INT32_MAX);
		if(old != body)
		{
			Sequence<T>::SList.Unbind();
		}
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
		throw MAE();
	}
}

template <typename T>
T &(ArraySequence<T>::operator[])(int index) const
{
	if((index < Sequence<T>::len) * (index >= 0))
	{
		return *(body[index]);
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
T &(ArraySequence<T>::GetFirst)() const
{
	if(Sequence<T>::len)
	{
		return **body;
	}
	else
	{
		throw CIE();
	}
}

template <typename T>
T &(ArraySequence<T>::GetLast)() const
{
	if(Sequence<T>::len)
	{
		return *(body[Sequence<T>::len - 1]);
	}
	else
	{
		throw CIE();
	}
}

template <typename T>
void ArraySequence<T>::Append(T &value)
{
	long int l = Sequence<T>::len;
	++l;
	l *= sizeof(T*);
	/*if(l > INT32_MAX)											//seems to be unnecessary, see extend()
	{
		throw MCE();
	}*/
	while(l > allocated_bytes)
	{
		extend();
	}
	body[(Sequence<T>::len++)] = &value;
}

template <typename T>
void ArraySequence<T>::Prepend(T &value)
{
	long int l = Sequence<T>::len;
	++l;
	l *= sizeof(T*);
	while(l > allocated_bytes)
	{
		extend();
	}
	for(int i = Sequence<T>::len; i > 0; i--)
	{
		body[i] = body[i-1];
	}
	body[0] = &value;
	++Sequence<T>::len;
}

template <typename T>
void ArraySequence<T>::Insert(T &value, int index)
{
	if((index > Sequence<T>::len) * (index < 0))
	{
		throw OoR();
	}
	long int l = Sequence<T>::len;
	++l;
	l *= sizeof(T*);
	while(l > allocated_bytes)
	{
		extend();
	}
	int i;
	for(i = Sequence<T>::len; i > index; i--)
	{
		body[i] = body[i - 1];
	}
	body[i] = &value;
	++Sequence<T>::len;
}

template <typename T>
void ArraySequence<T>::ForceLength(int length)
{
	if(length < 0)
	{
		throw NLE();
	}

	if(length*sizeof(T*) > allocated_bytes)
	{
		if(body)
		{
			body = (T**)realloc(body, length*sizeof(T*));
		}
		else if(length > 0)
		{
			body = (T**)malloc(length*sizeof(T*));
		}
	}
}

template <typename T>
void ArraySequence<T>::Remove(T &value)
{
	int i = 0;
	bool found = 0;
	while((i < Sequence<T>::len)*(!found))
	{
		if(*(body[i]) == value)
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
Sequence<T> *(ArraySequence<T>::GetSubS)(int start, int end) const
{
	if((end < Sequence<T>::len) * (start >= 0))
	{
		ArraySequence<T> *result = new ArraySequence<T>;
		for(int i = start; i <= end; i++)
		{
			result->Append(*(body[i]));
		}
		return result;
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
void ArraySequence<T>::SetRandVals(T *(*generator)(), int length)
{	
	if(length < 0)
	{
		throw NLE();
	}
	long int l = length*sizeof(T*);
	if(l > INT32_MAX)
	{
		throw MCE();
	}

	Clear();

	while(allocated_bytes < length*sizeof(T*))
	{
		extend();
	}
	Sequence<T>::len = length;
	
	T **tmp = body;
	
	for(int i = 0; i < length; i++)
	{
		*(tmp++) = generator();
	}
}

template <typename T>
typename Sequence<T>::Slider &(ArraySequence<T>::InitSlider)(int initpos) const
{
	if((initpos < Sequence<T>::len) * (initpos >= 0))
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
void ArraySequence<T>::ShiftPtrRight(void  *&ptr, int &position) const
{
	if(((position + 1) < Sequence<T>::len) * (position != INT32_MAX))			//assuming ptr size is more than 1 byte, 2nd comparison is extra, DO NOT DEL THE COMMENT until you fix all such 'mistakes'
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
void ArraySequence<T>::ShiftPtrLeft(void  *&ptr, int &position) const
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
T &(ArraySequence<T>::GetVal)(void *ptr) const
{
	return *(*(T**)ptr);
}

template <typename T>
void ArraySequence<T>::SetVal(T &val, void *ptr) const
{
	*((T**)ptr) = &val;
}

template <typename T>
ArraySequence<T>::~ArraySequence()
{
	free(body);
}
