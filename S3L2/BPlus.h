#include "malloc.h"

template <typename K, typename T>
class BPlus
{
private:
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

        EndNode() = delete;
        EndNode(int max_degree);
        ~EndNode();
    };


    int max_degree;
    Node *head;

public:
    BPlus() = delete;
    BPlus(int max_degree);

    T &Get(const K&) const;
    bool IsPresent(const K&) const;
    void Set(const K&, const T&);
    void Remove(const K&);

    ~BPlus();
};

#include "BPlus.cpp"
#include "EndNode.cpp"
#include "InterNode.cpp"