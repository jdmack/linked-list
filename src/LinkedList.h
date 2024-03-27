#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

class LinkedList
{
    class Node
    {
        public:
            Node();
            ~Node();

            Node * next_;
            Node * previous_;
            int * data_;
    };

    public:
        LinkedList();
        ~LinkedList();

        bool insert(int i);
        bool remove(int i);
        bool lookup(int i);

    private:
        Node * head_;
        Node * tail_;
        int occupancy_;



};



#endif