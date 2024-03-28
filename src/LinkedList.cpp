#include <sstream>
#include <exception>

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

void LinkedList::removeIndex(int index)
{
    // Verify index is within occupancy range
    if ((index < 0) || (index >= occupancy_))
        throw std::out_of_range(std::string(
            "index " + std::to_string(index) + 
            " out of range; occupancy=" + std::to_string(occupancy_)));

    Node * currentNode = head_;

    for (int i = 0; i < index; ++i) {
        if (currentNode != nullptr)
            currentNode = currentNode->next_;
    }
    removeNode(currentNode);
}


void LinkedList::lookup(int i)
{
}

void LinkedList::removeNode(Node * node)
{
    // Check if node is head (prev is null)
    if (node->previous_ == nullptr) {
        if (node->next_ != nullptr) {
            // Set the next node to be new head
            node->next_->previous_ = nullptr; 
        }
        head_ = node->next_;
    }
    else {
        // Node is not head
        node->previous_->next_ = node->next_;
    }

    // Check if node is tail (next is null)
    if (node->next_ == nullptr) { 
        if (node->previous_ != nullptr) {
            // Set the previous node to be new tail
            node->previous_->next_ = nullptr;
        }
        tail_ = node->previous_;
    }
    else {
        // Node is not tail
        node->next_->previous_ = node->previous_;
    }

    --occupancy_;
}

int & LinkedList::at(int index)
{
    // Verify index is within occupancy range
    if ((index < 0) || (index >= occupancy_))
        throw std::out_of_range(std::string(
            "index " + std::to_string(index) + 
            " out of range; occupancy=" + std::to_string(occupancy_)));

    Node * currentNode = head_;

    for (int i = 0; i < index; ++i) {
        if (currentNode != nullptr)
            currentNode = currentNode->next_;
    }
    return currentNode->data_;
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

