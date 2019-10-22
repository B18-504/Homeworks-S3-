#pragma once

template <typename T>
int Sequence<T>::GetLen() const
{
	return len;
}

template <typename T>
bool Sequence<T>::IsEmpty() const
{
	return !len;
}

template <typename T>
Sequence<T>::~Sequence()
{
	SList.Unbind();
}

template <typename T>
bool Sequence<T>::IsSorted(char comparison(T &a, T &b)) const
{
	bool result = 1;
	if(len > 1)
	{
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
			if(E.code != 0x12)				//!= OoR
			{
				throw E;
			}
		}
	}
	return result;
}
