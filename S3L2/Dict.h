#pragma once

template <typename K, typename T>
class Dict
{
public:

    virtual int GetCount() const = 0;
    virtual int CurrentCap() const = 0;                                   //-1 means "dont worry"
    virtual bool IsPresent(const K&) const = 0;

    virtual T &Get(const K&) const = 0;
    virtual void Set(const K&, const T&) = 0;
    virtual void Remove(const K&) = 0;

    virtual ~Dict() = default;
};

#include "BPlusDict.hpp"