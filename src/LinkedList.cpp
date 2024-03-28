#include <sstream>
#include <exception>

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList() :
    head_(nullptr),
    tail_(nullptr),
    occupancy_(0),
    recycleBin()
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* currentNode = head_;
    while (currentNode != nullptr) {
        Node<T>* deletePtr = currentNode;
        currentNode = currentNode->next_;
        delete deletePtr;
    }

    for (auto& node : recycleBin) {
        delete node;
    }
}

template <typename T>
void LinkedList<T>::insert(const T& data)
{
    Node<T>* newNode = allocateNode(data);

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

template <typename T>
void LinkedList<T>::insert(const T& data, int index)
{
    // Verify index is within occupancy range
    // For this check, index is allowed to be equal to occupancy as that would
    // be inserting at the tail
    if ((index < 0) || (index > occupancy_))
        throw std::out_of_range(std::string(
            "index " + std::to_string(index) + 
            " out of range; occupancy=" + std::to_string(occupancy_)));

    Node<T>* newNode = allocateNode(data);

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
        Node<T>* nodeAtIndex = getNode(index);

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

template <typename T>
void LinkedList<T>::remove(const T& data)
{
    Node<T>* currentNode = head_;

    while (currentNode != nullptr) {
        if (currentNode->data_ == data) {
            removeNode(currentNode);
            break;
        }

        currentNode = currentNode->next_;
    }
}

template <typename T>
void LinkedList<T>::removeIndex(int index)
{
    // Verify index is within occupancy range
    if ((index < 0) || (index >= occupancy_))
        throw std::out_of_range(std::string(
            "index " + std::to_string(index) + 
            " out of range; occupancy=" + std::to_string(occupancy_)));

    Node<T>* node = getNode(index);

    removeNode(node);
}


template <typename T>
int LinkedList<T>::lookup(const T& data)
{
    if (head_ == nullptr)
        return -1;

    int index = 0;
    Node<T>* currentNode = head_;

    while (currentNode != nullptr) {

        if (currentNode->data_ == data)
            return index;

        currentNode = currentNode->next_;
        ++index;
    }
    return -1;
}

template <typename T>
void LinkedList<T>::removeNode(Node<T>*& node)
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
    recycleNode(node);
    node = nullptr;
}

template <typename T>
T& LinkedList<T>::at(int index)
{
    // Verify index is within occupancy range
    if ((index < 0) || (index >= occupancy_))
        throw std::out_of_range(std::string(
            "index " + std::to_string(index) + 
            " out of range; occupancy=" + std::to_string(occupancy_)));

    Node<T>* node = getNode(index);

    return node->data_;
}

template <typename T>
LinkedList<T>::Node<T>* LinkedList<T>::getNode(int index)
{
    // Verify index is within occupancy range
    if ((index < 0) || (index >= occupancy_))
        return nullptr;

    Node<T>* currentNode = head_;

    // Iterate through list to the 'index'th element
    int i = 0;
    while ((currentNode != nullptr) && (i < index)) {
        currentNode = currentNode->next_;
        ++i;
    }
    return currentNode;
}

template <typename T>
LinkedList<T>::Node<T>* LinkedList<T>::allocateNode(const T& data)
{
    Node<T>* node;

    if (recycleBin.size() > 0) {
        node = recycleBin.front();
        recycleBin.pop_front();

        node->data_ = data;
        node->next_ = nullptr;
        node->previous_ = nullptr;
    }
    else {
        node = new Node<T>(data);
    }

    return node;
}

template <typename T>
void LinkedList<T>::recycleNode(Node<T>* node)
{
    if (recycleBin.size() >= occupancy_ * 0.25f) {
        delete node;
    }
    else {
        recycleBin.push_back(node);
    }
}


template <typename T>
std::string LinkedList<T>::toStr()
{
    Node<T>* currentNode = head_;
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

template <typename T>
std::string LinkedList<T>::toStrDetails()
{
    Node<T>* currentNode = head_;
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

template class LinkedList<int>;