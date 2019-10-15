#pragma once

template <typename T>
uint Sequence<T>::GetLen()
{
	return len;
}

template <typename T>
bool Sequence<T>::IsEmpty()
{
	return !len;
}

template <typename T>
Sequence<T>::~Sequence()
{
	SList.Unbind();
}

template <typename T>
bool Sequence<T>::IsSorted(char comparison(T &a, T &b))
{
	bool result = 1;
	if(len > 1)
	{
		RecoverSliders();
		T *current = (*this)[0], *next = (*this)[1];
		Slider &sl = InitSlider(1);
		try
		{
			while(result)
			{
				result = comparison(*current, *next);
				sl.ShiftRight();
				current = next;
				next = sl.GetVal();
			}
		}
		catch(Exception E)
		{
			if(E.code != 0x12)
			{
				throw E;
			}
		}
	}
	return result;
}
