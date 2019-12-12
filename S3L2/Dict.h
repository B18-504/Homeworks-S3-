#pragma once

template <typename K, typename T>
class Dict
{
protected:
    Dict() = default;

public:
    class Iterator
    {
    protected:
        Iterator() = default;

    public:
        virtual ~Iterator() = default;

        virtual T &Get() const = 0;
        virtual K &GetKey() const = 0;
        virtual bool HasNext() const = 0;
        virtual bool HasPrev() const = 0;
        virtual void ShiftRight() = 0;
        virtual void ShiftLeft() = 0;
    };

    virtual ~Dict() = default;

    virtual int GetCount() const = 0;
    virtual int CurrentCap() const = 0;                                   //-1 means "dont worry"
    virtual bool IsPresent(const K&) const = 0;

    virtual T &Get(const K&) const = 0;
    virtual void Set(const K&, const T&) = 0;
    virtual void Remove(const K&) = 0;

    virtual Iterator &StartIterator() const = 0;
};

#include "BPlusDict.hpp"