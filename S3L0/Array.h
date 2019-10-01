template <typename T>
class Array : public Sequence<T>
{
private:
	uint allocated_bytes = 0;
	T *body = 0;
	
	void extend();
	
public:
	
	Array() = default;
	
	T operator[](uint index) override;
	T GetFirst() override;
	T GetLast() override;
	
	Sequence<T> *GetSubS(uint start, uint end) override;
	
	void Append(T value) override;
	void Prepend(T value) override;
	void Insert(T value, uint index) override;
	void Remove(T value) override;
	
	~Array()
	{
		free(body);
	}
};

#include "Array.cpp"
