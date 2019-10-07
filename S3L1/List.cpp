#pragma once

template <typename T>
T *(List<T>::operator [])(uint index)
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
T *(List<T>::GetFirst)()
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
T *(List<T>::GetLast)()
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
void List<T>::Append(T *value)
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
void List<T>::Prepend(T *value)
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
}

template <typename T>
void List<T>::Insert(T *value, uint index)
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
}

template <typename T>
void List<T>::Remove(T *value)
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
}

template <typename T>
Sequence<T> *(List<T>::GetSubS)(uint start, uint end)
{
	if(end < Sequence<T>::len)
	{
		List<T> *result = new List<T>;
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
