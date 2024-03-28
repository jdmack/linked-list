#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <list>
#include <string>
/**
 * LinkedList implements a doubly linked list with template types
 * and basic Node recycling.
 */
template <class T>
class LinkedList
{
    /**
     * Node is a container for a single element in the list.
     * A copy of the data is created in the list.
     * It is specific to this implmentation of a LinkedList
     * so it is a nested class of LinkedList.
     * Uses the same template type passed to LinkedList.
     * 
     */
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

        std::list<Node<T>*> recycleBin_;

        void removeNode(Node<T>*& node);
        Node<T>* getNode(int index);

        Node<T>* allocateNode(const T& data);
        void recycleNode(Node<T>* node);
};

#endif