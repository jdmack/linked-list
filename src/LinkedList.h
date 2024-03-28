#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <string>
class LinkedList
{
    class Node
    {
        public:
            Node() { }
            Node(int i) : next_(nullptr), previous_(nullptr), data_(i) { } 
            ~Node();

            Node * next_ {nullptr};
            Node * previous_ {nullptr};
            int data_ {0};
    };

    public:
        LinkedList();
        ~LinkedList();

        void insert(int i);
        void remove(int i);
        void lookup(int i);

        int & at(int index);
        void removeIndex(int index);

        int & operator [](int index) { return at(index); }

        std::string toStr();

    private:
        Node * head_;
        Node * tail_;
        int occupancy_;

        void removeNode(Node * node);

};



#endif