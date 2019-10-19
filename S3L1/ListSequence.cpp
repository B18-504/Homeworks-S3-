#pragma once

template <typename T>
T *(ListSequence<T>::operator [])(uint index) const
{
	if(index < Sequence<T>::len)
	{
		Node *tmp = first;
		for(uint i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		return tmp->body;
	}
	else
	{
		throw(OoR());
	}
}

template <typename T>
T *(ListSequence<T>::GetFirst)() const
{
	if(Sequence<T>::len)
	{
		return first->body;
	}
	else
	{
		throw(CIE());
	}
}

template <typename T>
T *(ListSequence<T>::GetLast)() const
{
	if(Sequence<T>::len)
	{
		return last->body;
	}
	else
	{
		throw(CIE());
	}
}

template <typename T>
void ListSequence<T>::Append(T *value)
{
	if(Sequence<T>::len == -1u)
	{
		throw(MSR());
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
	if(Sequence<T>::len == -1u)
	{
		throw(MSR());
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
void ListSequence<T>::Insert(T *value, uint index)
{
	if(index > Sequence<T>::len)
	{
		throw(OoR());
	}
	if(Sequence<T>::len == -1u)
	{
		throw(MSR());
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
		for(uint i = 0; i < (index-1); i++)
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
	uint i = 0;
	bool found = 0;
	Node *tmp = first;
	while((i < Sequence<T>::len)*(!found))
	{
		if(*(tmp->body) == *value)
		{
			found = 1;	
		}
		else
		{
			tmp = tmp->next;
			++i;
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
	Node *next = 0;
	while(tmp)
	{
		next = tmp->next;
		delete tmp;
		tmp = next;
	}
	first = 0;
	last = 0;
	Sequence<T>::len = 0;
}

template <typename T>
Sequence<T> *(ListSequence<T>::GetSubS)(uint start, uint end) const
{
	if(end < Sequence<T>::len)
	{
		ListSequence<T> *result = new ListSequence<T>;
		Node *tmp = first;
		uint i = 0;
		
		for(i; i < start; i++)
		{
			tmp = tmp->next;
		}
		
		for(i; i <= end; i++)
		{
			result->Append(tmp->body);
		}
		
		return result;
	}
	else
	{
		throw(OoR());
	}
}

template <typename T>
void ListSequence<T>::SetFromStr(char **values, uint length)
{
	Node *tmp;
	while(first)
	{
		tmp = first->next;
		delete first;
		first = tmp;
	}
	last = 0;
	Sequence<T>::len = 0;
	
	for(uint i = 0; i < length; i++)
	{
		Append(StrToNumber(*(values++)));
	}
}

template <typename T>
void ListSequence<T>::SetRandVals(T *(*generator)(), uint length)
{
	Node *tmp;
	while(first)
	{
		tmp = first->next;
		delete first;
		first = tmp;
	}
	last = 0;
	Sequence<T>::len = 0;
	
	for(uint i = 0; i < length; i++)
	{
		Append(generator());
	}
}

template <typename T>
typename Sequence<T>::Slider &(ListSequence<T>::InitSlider)(uint initpos) const
{
	if(initpos < Sequence<T>::len)
	{
		ListSequence<T>::Node *nd;
		if(initpos < Sequence<T>::len)
		{
			nd = first;
			for(uint i = 0; i < initpos; i++)
			{
				nd = nd->next;
			}
		}
		else
		{
			nd = last;
			for(uint i = Sequence<T>::len - 1; i > initpos; i--)
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
void ListSequence<T>::ShiftPtrRight(void  *&ptr, uint &position) const
{
	if(((position + 1) < Sequence<T>::len) * (position != -1u))
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
void ListSequence<T>::ShiftPtrLeft(void  *&ptr, uint &position) const
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
	Node *tmp = first;
	Node *next = 0;
	while(tmp)
	{
		next = tmp->next;
		delete tmp;
		tmp = next;
	}
}
