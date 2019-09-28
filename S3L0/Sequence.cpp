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
