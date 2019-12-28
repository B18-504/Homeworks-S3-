#pragma once

template <typename P, typename T>
class PriorityQueue
{
protected:
    PriorityQueue() = default;

public:
    virtual ~PriorityQueue() = default;

    virtual int GetCount() const = 0;
    virtual void Enqueue(const P&, const T&) = 0;
    virtual void Dequeue(P*&, T*&) = 0;
};

#include "BPlusPriorityQueue.hpp"