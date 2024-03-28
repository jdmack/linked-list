#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <list>
#include <string>
template <class T>
class LinkedList
{
    template <class T2>
    class Node
    {
        public:
            Node() { }
            Node(const T2& data) : next_(nullptr), previous_(nullptr), data_(data) { } 
            ~Node() { };

            Node<T2>* next_ {nullptr};
            Node<T2>* previous_ {nullptr};
            T2 data_;
    };

    public:
        LinkedList();
        ~LinkedList();

        void insert(const  T& data);
        void insert(const  T& data, int index);
        void remove(const  T& data);
        void removeIndex(int index);
        int lookup(const  T& data);

        T& at(int index);

        T& operator [](int index) { return at(index); }

        int size() { return occupancy_; }

        std::string toStr();
        std::string toStrDetails();

    private:
        Node<T>* head_;
        Node<T>* tail_;
        int occupancy_;

        std::list<Node<T>*> recycleBin;

        void removeNode(Node<T>*& node);
        Node<T>* getNode(int index);

        Node<T>* allocateNode(const T& data);
        void recycleNode(Node<T>* node);
};

#endif