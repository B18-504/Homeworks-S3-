#pragma once

template <typename T>
T *(ListSequence<T>::operator [])(int index) const
{
	if((index >= 0) * (index < Sequence<T>::len))
	{
		if(index < Sequence<T>::len/2)
		{
			Node *tmp = first;
			for(int i = 0; i < index; i++)
			{
				tmp = tmp->next;
			}
			return tmp->body->Clone();
		}
		else
		{
			Node *tmp = last;
			for(int i = Sequence<T>::len - 1; i > index; i--)
			{
				tmp = tmp->prev;
			}
			return tmp->body->Clone();
		}
		
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
T *(ListSequence<T>::GetFirst)() const
{
	if(Sequence<T>::len)
	{
		return first->body->Clone();
	}
	else
	{
		throw CIE();
	}
}

template <typename T>
T *(ListSequence<T>::GetLast)() const
{
	if(Sequence<T>::len)
	{
		return last->body->Clone();
	}
	else
	{
		throw CIE();
	}
}

template <typename T>
void ListSequence<T>::Append(T *value)
{
	if(Sequence<T>::len == INT32_MAX)
	{
		throw MCE();
	}
	if(Sequence<T>::len)
	{
		last->next = new Node(value->Clone(), 0, last);
		last = last->next;
	}
	else
	{
		first = new Node(value->Clone());
		last = first;
	}
	++Sequence<T>::len;
}

template <typename T>
void ListSequence<T>::Prepend(T *value)
{
	if(Sequence<T>::len == INT32_MAX)
	{
		throw MCE();
	}
	if(Sequence<T>::len)
	{
		first->prev = new Node(value->Clone(), first, 0);
		first = first->prev;
	}
	else
	{
		first = new Node(value->Clone());
		last = first;
	}
	++Sequence<T>::len;
	Sequence<T>::SList.Unbind();
}

template <typename T>
void ListSequence<T>::Insert(T *value, int index)
{
	if((index > Sequence<T>::len) * (index < 0))
	{
		throw OoR();
	}
	if(Sequence<T>::len == INT32_MAX)
	{
		throw MCE();
	}

	else if(index == 0)
	{
		Prepend(value);
	}
	else if(index == Sequence<T>::len)
	{
		Append(value);
	}
	else
	{
		Node *tmp = first;
		for(int i = 0; i < (index-1); i++)
		{
			tmp = tmp->next;
		}
		tmp->next = new Node(value->Clone(), tmp->next, tmp);
		tmp->next->next->prev = tmp->next;
	}
	++Sequence<T>::len;
	Sequence<T>::SList.Unbind();
}

template <typename T>
void ListSequence<T>::Remove(T *value)
{
	bool found = 0;
	Node *tmp = first;
	while(bool(tmp)*!bool(found))
	{
		if(*(tmp->body) == *value)
		{
			found = 1;	
		}
		else
		{
			tmp = tmp->next;
		}
	}
	if(found)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		delete tmp;
		--Sequence<T>::len;
	}
	Sequence<T>::SList.Unbind();
}

template <typename T>
void ListSequence<T>::Clear()
{
	Node *tmp = first;
	while(tmp)
	{
		tmp = first->next;
		delete first;
		first = tmp;
	}
	first = 0;
	last = 0;
	Sequence<T>::len = 0;
}

template <typename T>
Sequence<T> *(ListSequence<T>::GetSubS)(int start, int end) const
{
	if((end < Sequence<T>::len) * (start >= 0))
	{
		ListSequence<T> *result = new ListSequence<T>;
		Node *tmp = first;
		int i = 0;
		
		for(i; i < start; i++)
		{
			tmp = tmp->next;
		}
		
		for(i; (i <= end) * (i >= 0); i++)													//i >= 0 is checking for overflow
		{
			result->Append(tmp->body);
			tmp = tmp->next;
		}
		
		return result;
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
void ListSequence<T>::SetFromStr(char **values, int length)
{
	if(length < 0)
	{
		throw NLE();
	}

	Clear();
	
	for(int i = 0; (i < length) * (i >= 0); i++)
	{
		Append(StrToNumber(*(values++)));
	}
}

template <typename T>
void ListSequence<T>::SetRandVals(T *(*generator)(), int length)
{
	if(length < 0)
	{
		throw NLE();
	}

	Clear();
	
	for(int i = 0; (i < length) * (i >= 0); i++)
	{
		Append(generator());
	}
}

template <typename T>
typename Sequence<T>::Slider &(ListSequence<T>::InitSlider)(int initpos) const
{
	if((initpos < Sequence<T>::len) * (initpos >= 0))
	{
		ListSequence<T>::Node *nd;
		if(initpos < (Sequence<T>::len)/2)
		{
			nd = first;
			for(int i = 0; i < initpos; i++)											//in this case initpos is definetly less than INT32_MAX, no need in overflow check
			{
				nd = nd->next;
			}
		}
		else
		{
			nd = last;
			for(int i = Sequence<T>::len - 1; i > initpos; i--)
			{
				nd = nd->prev;
			}
		}
		typename Sequence<T>::Slider *tmp = new (typename Sequence<T>::Slider)(this, nd, initpos);
		Sequence<T>::SList.Append(tmp);
		return(*(Sequence<T>::SList.last->body));
	}
	else
	{
		return *new typename Sequence<T>::Slider;
	}
}


template <typename T>
void ListSequence<T>::ShiftPtrRight(void  *&ptr, int &position) const
{
	if(position < (Sequence<T>::len - 1))
	{
		ptr = ((ListSequence<T>::Node*)ptr)->next;
		++position;
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
void ListSequence<T>::ShiftPtrLeft(void  *&ptr, int &position) const
{
	if(position != 0)
	{
		ptr = ((ListSequence<T>::Node*)ptr)->prev;
		--position;
	}
	else
	{
		throw OoR();
	}
}

template <typename T>
T *(ListSequence<T>::GetVal)(void *ptr) const
{
	return ((Node*)ptr)->body;
}

template <typename T>
void ListSequence<T>::SetVal(T *val, void *ptr) const
{
	((ListSequence<T>::Node*)ptr)->body = val;
}

template <typename T>
ListSequence<T>::~ListSequence()
{
	Clear();
}
