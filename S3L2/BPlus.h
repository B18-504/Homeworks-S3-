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
        virtual bool IsPresent(const K&) const = 0;
        virtual Node *Set(K&, T&) = 0;
        virtual bool Remove(const K&) = 0;
        virtual K &GetLeastKey() const = 0;

        virtual Node *StartIterator() const = 0;

        virtual ~Node() = default;
    };


    class InterNode : public Node
    {
    public:
        Node **nodes;
        InterNode *left, *right;

        T &Get(const K&) const override;
        bool IsPresent(const K&) const override;
        Node *Set(K&, T&) override;
        bool Remove(const K&) override;
        K &GetLeastKey() const override;

        Node *StartIterator() const override;

        InterNode() = delete;
        InterNode(int max_degree);
        ~InterNode();
    };

    class EndNode : public Node
    {
    public:
        T **values;
        EndNode *left, *right;

        T &Get(const K&) const override;
        bool IsPresent(const K&) const override;
        Node *Set(K&, T&) override;
        bool Remove(const K&) override;
        K &GetLeastKey() const override;

        Node *StartIterator() const override;

        EndNode *ShiftRight(int&) const;              //interface for Iterator
        EndNode *ShiftLeft(int&) const;
        bool HasNext(int) const;
        bool HasPrev(int) const;
        T &GetI(int) const;
        K &GetKey(int) const;

        EndNode() = delete;
        EndNode(int max_degree);
        ~EndNode();
    };


    int max_degree;
    Node *head;

    int count;

    EndNode *StartIterator();

public:
    class Iterator
    {
    private:
        EndNode *curr_node;
        int curr_pos;
    
    public:
        Iterator() = delete;
        Iterator(BPlus<K, T>&);
        ~Iterator() = default;

        T &Get() const;
        K &GetKey() const;
        bool HasNext() const;
        bool HasPrev() const;
        void ShiftRight();
        void ShiftLeft();
    };


    BPlus() = delete;
    BPlus(int max_degree);

    T &Get(const K&) const;
    bool IsPresent(const K&) const;
    int GetCount() const;
    void Set(const K&, const T&);
    void Remove(const K&);

    ~BPlus();
};

#include "BPlus.cpp"
#include "EndNode.cpp"
#include "InterNode.cpp"
#include "Iterator.cpp"