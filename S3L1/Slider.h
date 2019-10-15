template <typename T>
class Sequence<T>::Slider
{
private:
	Sequence *master = 0;
	void *ptr = 0;
	uint position;
	void *node;															//ptr to node, that stores ptr to this Slider
	
	Slider()
	{}
	Slider(Sequence *seq, void *p, uint initpos);
	
	void Unbind();
public:
	T *GetVal();
	void SetVal(T *a);
	
	void ShiftRight();
	void ShiftLeft();
	
	bool IsBound();
	
	~Slider();
	
	friend class SliderList;
	friend class Sequence<T>;
	friend class Array<T>;
	friend class List<T>;
};

template <typename T>
class Sequence<T>::SliderList
{
public:
	class SliderNode;
	
	SliderNode *first = 0;
	SliderNode *last = 0;
	
	void Append(Slider *sldr);
	void Unbind();
};

template <typename T>
class Sequence<T>::SliderList::SliderNode
{
public:
	Slider *body = 0;
	SliderNode *next = 0;
	SliderNode *prev = 0;
};

template <typename T>
void swap(typename Sequence<T>::Slider &a, typename Sequence<T>::Slider &b);


#include "Slider.cpp"
