#pragma once

template <typename T>
struct Call;

template <typename T>
struct CallStack;

template <typename T>
void push(CallStack<T> &CS, Call<T> &C);

template <typename T>
void push(CallStack<T> &CS, typename Sequence<T>::Slider *left, typename Sequence<T>::Slider *right);

template <typename T>
void push_start(CallStack<T> &CS);

template <typename T>
void push_shift(CallStack<T> &CS);

template <typename T>
void pop(CallStack<T> &CS, Call<T> *&buff);

#include "CallStack.cpp"