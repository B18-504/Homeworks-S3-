template <typename T>
class Array : public Sequence<T>
{
private:
	uint allocated_bytes = 0;
	T *body = 0;
	
	void extend();
	
public:
	T operator[](uint index) override;
	T GetFirst() override;
	T GetLast() override;
	Array<T> *GetSubs(uint start, uint end);
	void Append(T value) override;
	void Prepend(T value) override;
	void Insert(T value, uint index) override;
};

#include "Array.cpp"
