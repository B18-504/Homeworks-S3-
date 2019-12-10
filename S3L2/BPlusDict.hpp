#pragma once
#include "BPlus.h"

template <typename K, typename T>
class BPlusDict : public Dict<K, T>
{
private:
    BPlus<K, T> *body;

public:
    BPlusDict(int max_grade)
    {
        body = new BPlus<K, T>(max_grade);
    }

    ~BPlusDict()
    {
        delete body;
    }

    int GetCount() const override
    {
        return body->GetCount();
    }

    int CurrentCap() const override
    {
        return -1;
    }

    bool IsPresent(const K& key) const override
    {
        return body->IsPresent(key);
    }

    T &Get(const K& key) const override
    {
        return body->Get(key);
    }

    void Set(const K& key, const T& value) override
    {
        body->Set(key, value);
    }

    void Remove(const K& key) override
    {
        body->Remove(key);
    }
};