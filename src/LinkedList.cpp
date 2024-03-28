#include <sstream>
#include <exception>

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList() :
    head_(nullptr),
    tail_(nullptr),
    occupancy_(0),
    recycleBin_()
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    // delete all nodes in the list
    Node<T>* currentNode = head_;
    while (currentNode != nullptr) {
        Node<T>* deletePtr = currentNode;
        currentNode = currentNode->next_;
        delete deletePtr;
    }

    // delete all nodes in recycle bin
    for (auto& node : recycleBin_) {
        delete node;
    }
}

/**
 * @brief  Insert a data value into the list
 *
 * Makes a copy of the data value and creates a new Node
 * in the list to hold the data whiich is added to the tail.
 *
 * @param  data:  The value to insert, template type
 */
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

/**
 * @brief  Insert a data value into the list at a specific index
 *
 * Makes a copy of the data value and creates a new Node
 * in the list to hold the data and inserts it at the specified
 * index, placing it in front of the Node currently at that index.
 *
 * @param  data:  The value to insert, template type
 * @param  index:  Index to insert data to
 * 
 * @throws std::out_of_range
 */
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

/**
 * @brief  Remove the specified data from the list
 *
 * This function finds the Node that matches the specified
 * data value and removes it from the list.
 *
 * @param  data:  The value to insert, template type
 */
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

/**
 * @brief  Remove data from the list at the specified index
 *
 * @param  index:  The index to remove
 * 
 * @throws std::out_of_range
 */
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

/**
 * @brief  Lookup a specified data value in the list
 *
 * Search the list linearly and find the Node that
 * contains the specified data value.
 *
 * @param  data:  The value to find
 * 
 * @return  the first index where the data was found
 *          -1 if not found
 */
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

/**
 * @brief  Remove Node from the list
 *
 * Internal function to remove a specified Node
 * from the list and delete it.
 *
 * @param  node:  A pointer to the Node to remove
 *                Pointer is a reference so that it can be
 *                cleared
 */
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

/**
 * @brief  Access the data at a specific index
 *
 * Data is modifiable.
 *
 * @param  index:  The  index to acccess
 * 
 * @throws std::out_of_range
 * 
 * @return  Reference to the data at that index, template type
 */
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

/**
 * @brief  Get a pointer to the Node at the specified index
 *
 * Internal function to traverse list by index.
 *
 * @param  index:  The index of which Node to get
 * 
 * @return  A pointer to the Node at the specified index
 *          nullptr if index invalid
 */
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

/**
 * @brief  Create a Node with specified data
 *
 * Internal function that is used to create Nodes as they are needed.
 * It first checks if there are any recycled Nodes available
 * and if not, allocates a new one. The data is then stored in it.
 * 
 * Recycled Nodes are to reduce the number of memory operations performed.
 *
 * @param  data:  The data value to store in Node
 * 
 * @return  A pointer to the new Node
 */
template <typename T>
LinkedList<T>::Node<T>* LinkedList<T>::allocateNode(const T& data)
{
    Node<T>* node;

    if (recycleBin_.size() > 0) {
        node = recycleBin_.front();
        recycleBin_.pop_front();

        node->data_ = data;
        node->next_ = nullptr;
        node->previous_ = nullptr;
    }
    else {
        node = new Node<T>(data);
    }

    return node;
}

/**
 * @brief  Recycle a Node to be reused or deleted
 *
 * Internal function used when Nodes are removed from the
 * list. Instead of deallocating the Nodes, they are placed
 * in a list to be used for new insertions. We only store at most
 * 1/4-of-the-list-size Nodes.
 * 
 * @param  node:  The Node to recycle
 */
template <typename T>
void LinkedList<T>::recycleNode(Node<T>* node)
{
    if (recycleBin_.size() >= occupancy_ * 0.25f) {
        delete node;
    }
    else {
        recycleBin_.push_back(node);
    }
}


/**
 * @brief  Creates a string representation of the list
 *
 * Iterates through the list and builds up a string representation
 * of the list. Requires the template type to have the stream insertion
 * operator defined. Used for tests.
 *
 * @return  std::string representation of the list
 */
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

/**
 * @brief  Creates a string representation of the list with details
 *
 * Iterates through the list and builds up a string representation
 * of the list. Requires the template type to have the stream insertion
 * operator defined. This function provides additional details to assist
 * in debugging.
 *
 * @return  std::string representation of the list
 */
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