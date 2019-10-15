template <typename T>
Sequence<T>::Slider::Slider(Sequence<T> *seq, void *p, uint initpos)
{
	master = seq;
	ptr = p;
	position = initpos;
}

template <typename T>
void Sequence<T>::SliderList::Append(Slider *sldr)
{
	SliderNode *tmp = new SliderNode;
	if(bool(last))
	{
		tmp->prev = last;
		last->next = tmp;
		last = last->next;
	}
	else
	{
		first = new SliderNode;
		last = first;
	}
	last->body = sldr;
	last->body->node = tmp;
}

template <typename T>
void Sequence<T>::Slider::Unbind()
{
	if(((typename SliderList::SliderNode*)node)->next)
	{
		((typename SliderList::SliderNode*)node)->next->prev = ((typename SliderList::SliderNode*)node)->prev;
	}
	else
	{
		master->SList.last = ((typename SliderList::SliderNode*)node)->prev;
	}
	if(((typename SliderList::SliderNode*)node)->prev)
	{
		((typename SliderList::SliderNode*)node)->prev->next = ((typename SliderList::SliderNode*)node)->next;
	}
	else
	{
		master->SList.first = ((typename SliderList::SliderNode*)node)->next;
	}
	master = 0;
	delete node;
	node = 0;
}

template <typename T>
void Sequence<T>::SliderList::Unbind()
{
	SliderNode *tmp = first;
	while(tmp)
	{
		tmp->body->node = 0;
		tmp->body->master = 0;
		tmp = tmp->next;
	}
}

template <typename T>													
Sequence<T>::Slider::~Slider()
{
	if(((typename SliderList::SliderNode*)node)->next)
	{
		((typename SliderList::SliderNode*)node)->next->prev = ((typename SliderList::SliderNode*)node)->prev;
	}
	else
	{
		master->SList.last = ((typename SliderList::SliderNode*)node)->prev;
	}
	if(((typename SliderList::SliderNode*)node)->prev)
	{
		((typename SliderList::SliderNode*)node)->prev->next = ((typename SliderList::SliderNode*)node)->next;
	}
	else
	{
		master->SList.first = ((typename SliderList::SliderNode*)node)->next;
	}
}

template <typename T>
T *(Sequence<T>::Slider::GetVal)()
{
	if(!master)
	{
		throw SIU();
	}
	return master->GetVal(ptr);
}

template <typename T>
void Sequence<T>::Slider::SetVal(T *a)
{
	master->SetVal(a, ptr);
}

template <typename T>
void (Sequence<T>::Slider::ShiftLeft())
{
	if(!master)
	{
		throw SIU();
	}
	master->ShiftPtrLeft(ptr, position);
}

template <typename T>
void (Sequence<T>::Slider::ShiftRight())
{
	if(!master)
	{
		throw SIU();
	}
	master->ShiftPtrRight(ptr, position);
}

template <typename T>
bool Sequence<T>::Slider::IsBound()
{
	return bool(master);
}

template <typename T>
void swap(typename Sequence<T>::Slider &a, typename Sequence<T>::Slider &b)
{
	T *tmp = a.GetVal();
	a.SetVal(b.GetVal());
	b.SetVal(tmp);
}
