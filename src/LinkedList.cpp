#include <sstream>

#include "LinkedList.h"

LinkedList::LinkedList() :
    head_(nullptr),
    tail_(nullptr),
    occupancy_(0)
{
}

LinkedList::~LinkedList()
{
}

void LinkedList::insert(int i)
{
    Node * newNode = new Node(i);

    if (head_ == nullptr) {
        head_ = newNode;
        tail_ =  newNode;
    }
    else {
        tail_->next_ = newNode;
        newNode->previous_ = tail_;
        tail_ = newNode;
    }
    ++occupancy_;
}

void LinkedList::remove(int i)
{
    Node * currentNode = head_;

    while (currentNode != nullptr) {

        if (currentNode->data_ == i) {
            removeNode(currentNode);
            break;
        }

        currentNode = currentNode->next_;
    }
}

void LinkedList::lookup(int i)
{
}

void LinkedList::removeNode(Node * node)
{

    if (node->previous_ == nullptr) {
        if (node->next_ != nullptr)
            node->next_->previous_ = nullptr; 
        head_ = node->next_;
    }
    else {
        node->previous_->next_ = node->next_;
    }

    if (node->next_ == nullptr) { 
        if (node->previous_ != nullptr)
            node->previous_->next_ = nullptr;
        tail_ = node->previous_;
    }
    else {
        node->next_->previous_ = node->previous_;
    }

    --occupancy_;
}

std::string LinkedList::toStr()
{
    Node * currentNode = head_;
    std::stringstream ss;    
    bool first = true;
    
    ss << "[";

    while (currentNode != nullptr) {
        if (first == false)
            ss << " ";
        else
            first = false;

        ss << currentNode->data_;
        currentNode = currentNode->next_;
    }

    ss << "]";

    return ss.str();
}

