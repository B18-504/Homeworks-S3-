#pragma once

#include "BPlus.h"

template <typename P, typename T>
class BPlusPriorityQueue : public PriorityQueue<P, T>
{
private:
    BPlus<P, T> *body = 0;

public:
    BPlusPriorityQueue() = delete;
    BPlusPriorityQueue(int max_grade)
    {
        if(body)
        {
            delete body;
        }

        body = new BPlus<P, T>(max_grade);
    }
    ~BPlusPriorityQueue()
    {
        if(body)
        {
            delete body;
        }
    }

    int GetCount() const override
    {
        return body->GetCount();
    }

    void Enqueue(const P &priority, const T &value) override
    {
        body->Add(priority, value);
    }

    void Dequeue(P *&priority, T *&value) override
    {
        body->PopFirst(priority, value);
    }
};