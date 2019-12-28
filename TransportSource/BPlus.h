#pragma once

#include "malloc.h"

template <typename K, typename T>
class BPlus
{
private:
    friend class Iterator;

    class Node
    {
    public:
        int max_degree;
        int used_keys;
        K **keys;

        virtual T &Get(const K&) const = 0;
        virtual bool PopFirst(K *&, T *&) = 0;
        virtual bool IsPresent(const K&) const = 0;
        virtual Node *Add(K&, T&) = 0;
        //virtual bool Remove(const K&) = 0;
        virtual K &GetLeastKey() const = 0;

        virtual Node *StartIterator() const = 0;

        virtual void *ShareValRight() = 0;
        virtual K &ShareKeyRight() = 0;
        virtual void TakeValRight(void*) = 0;
        void TakeKeyRight(K&);
        virtual void Absorb(Node*) = 0;

        virtual bool RootToBeRemoved() const = 0;

        virtual ~Node() = default;
    };


    class InterNode : public Node
    {
    public:
        Node **nodes;
        InterNode *left, *right;

        T &Get(const K&) const override;
        bool PopFirst(K *&, T *&) override;
        bool IsPresent(const K&) const override;
        Node *Add(K&, T&) override;
        //bool Remove(const K&) override;
        K &GetLeastKey() const override;

        Node *StartIterator() const override;

        K &ShareKeyRight() override;
        void *ShareValRight() override;
        void TakeValRight(void*) override;
        void Absorb(Node*) override;

        bool RootToBeRemoved() const override;

        InterNode() = delete;
        InterNode(int max_degree);
        ~InterNode();
    };

    class EndNode : public Node
    {
    private:
        T &GetI(int) const;
        void SetI(const T&, int);

        friend class BPlus<K, T>::Iterator;
    
    public:
        T **values;
        EndNode *left, *right;

        T &Get(const K&) const override;
        bool PopFirst(K *&, T *&) override;
        bool IsPresent(const K&) const override;
        Node *Add(K&, T&) override;
        //bool Remove(const K&) override;
        K &GetLeastKey() const override;

        Node *StartIterator() const override;

        EndNode *ShiftRight(int&) const;              //interface for Iterator
        EndNode *ShiftLeft(int&) const;
        bool HasNext(int) const;
        bool HasPrev(int) const;
        K &GetKey(int) const;

        K &ShareKeyRight() override;
        void *ShareValRight() override;
        void TakeValRight(void*) override;
        void Absorb(Node*) override;

        bool RootToBeRemoved() const override;

        EndNode() = delete;
        EndNode(int max_degree);
        ~EndNode();
    };

public:
    class Iterator
    {
    private:
        EndNode *curr_node;
        int curr_pos;
    
    public:
        Iterator() = delete;
        Iterator(const BPlus<K, T>&);
        ~Iterator() = default;

        T &Get() const;
        K &GetKey() const;
        void Set(const T&) const;
        bool HasNext() const;
        bool HasPrev() const;
        void ShiftRight();
        void ShiftLeft();
    };

private:
    int max_degree;
    Node *head;
    EndNode *first;

    int count;

    Node *StartIterator() const;

public:


    BPlus() = delete;
    BPlus(int max_degree);

    T &Get(const K&) const;
    void PopFirst(K *&, T *&);
    bool IsPresent(const K&) const;
    int GetCount() const;
    void Add(const K&, const T&);
    //void Remove(const K&);

    ~BPlus();
};

#include "BPlus.cpp"
#include "EndNode.cpp"
#include "InterNode.cpp"
//#include "BPlusIterator.cpp"