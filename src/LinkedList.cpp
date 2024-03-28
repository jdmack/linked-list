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

void LinkedList::insert(int i, int index)
{
    // Verify index is within occupancy range
    // For this check, index is allowed to be equal to occupancy as that would
    // be inserting at the tail
    if ((index < 0) || (index > occupancy_))
        throw std::out_of_range(std::string(
            "index " + std::to_string(index) + 
            " out of range; occupancy=" + std::to_string(occupancy_)));

    Node * newNode = new Node(i);

    // If index is at end, insert after use tail, otherwise insert in front of index node
    if (index == occupancy_) {
        // Special case when inserting at 0 into empty list
        if (tail_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            tail_->next_ = newNode;
            newNode->previous_ = tail_;
            tail_ = newNode;
        }
    }
    else {
        Node * nodeAtIndex = getNode(index);

        newNode->next_ = nodeAtIndex;
        newNode->previous_ = nodeAtIndex->previous_;

        // If inserting at front, assign new head
        if (nodeAtIndex == head_)
            head_ = newNode;
        else
            nodeAtIndex->previous_->next_ = newNode;

        nodeAtIndex->previous_ = newNode;

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

    Node * node = getNode(index);

    removeNode(node);
}


int LinkedList::lookup(int i)
{

}

void LinkedList::removeNode(Node * node)
{
    if (node == nullptr)
        return;

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

    Node * node = getNode(index);

    return node->data_;
}
LinkedList::Node * LinkedList::getNode(int index)
{
    // Verify index is within occupancy range
    if ((index < 0) || (index >= occupancy_))
        return nullptr;

    Node * currentNode = head_;

    // Iterate through list to the 'index'th element
    int i = 0;
    while ((currentNode != nullptr) && (i < index)) {
        currentNode = currentNode->next_;
        ++i;
    }
    return currentNode;
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

std::string LinkedList::toStrDetails()
{
    Node * currentNode = head_;
    std::stringstream ss;    
    
    ss << "[";

    ss << "head=";

    if (head_ == nullptr)
        ss << "n";
    else
        ss << head_->data_;

    ss << ", tail=";

    if (tail_ == nullptr)
        ss << "n";
    else
        ss << tail_->data_;

    while (currentNode != nullptr) {
        ss << "\n\t(prev=";

        if (currentNode->previous_ == nullptr)
            ss << "n";
        else
            ss << currentNode->previous_->data_;

        ss << ", data=" << currentNode->data_ << ", next=";

        if (currentNode->next_ == nullptr)
            ss << "n";
        else
            ss << currentNode->next_->data_;

        ss << ")";

        currentNode = currentNode->next_;
    }

    ss << "\n]";

    return ss.str();
}
