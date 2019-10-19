template <typename T>
struct Call
{
    typename Sequence<T>::Slider *left, *right;
    char cond;
    Call *prev;
};

template <typename T>
struct CallStack
{
    Call<T> *head = 0;
};

template <typename T>
void push(CallStack<T> &CS, Call<T> &C)
{
    C.prev = CS.head;
    CS.head = &C;
}

template <typename T>
void push(CallStack<T> &CS, typename Sequence<T>::Slider *left, typename Sequence<T>::Slider *right)
{
    Call<T> &tmp = *(Call<T>*)malloc(sizeof(Call<T>));
    tmp.left = left;
    tmp.right = right;
    tmp.cond = 0;
    push(CS, tmp);
}

template <typename T>
void push_start(CallStack<T> &CS)
{
    Call<T> &tmp = *(Call<T>*)malloc(sizeof(Call<T>));
    tmp.cond = 2;
    push(CS, tmp);
}

template <typename T>
void push_shift(CallStack<T> &CS)
{
    Call<T> &tmp = *(Call<T>*)malloc(sizeof(Call<T>));
    tmp.cond = 1;
    push(CS, tmp);
}

template <typename T>
void pop(CallStack<T> &CS, Call<T> *&buff)
{
    if(CS.head)
    {
        buff = CS.head;
        CS.head = buff->prev;
        buff->prev = 0;
    }
    else
    {
        throw NPE();
    }
}
