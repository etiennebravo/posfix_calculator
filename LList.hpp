/// @file LList.hpp
/// @author Etienne Bravo
/// @date 12/3/2023
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
///
/// @brief Template file for node lists contructs, creates lists

#ifndef LLIST_HPP
#define LLIST_HPP

#include <iterator>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <utility>

/// Node is a Struct that creates values with pointers to previous and
/// following nodes (if any). Used by LList class to create linked lists that
/// support insertion and removal of nodes.

template <class T>
struct Node {
    using value_type = T;

    // Construct
    Node(const value_type& value, Node* prev_node = nullptr,
                                  Node* next_node = nullptr)
    : data(value), prev(prev_node), next(next_node) {}

    value_type data;   ///< Data of the node, of type T
    Node*      prev;   ///< Pointer to the previous node
    Node*      next;   ///< Pointer to the next node
};

/// List is a container that supports constant time insertion and removal of
/// elements from anywhere in the container. Fast random access is not
/// supported. It is implemented as a doubly-linked list. This container
/// provides bidirectional iteration capability.
///
/// Adding, removing and moving the elements within the list or across several
/// lists does not invalidate the iterators or references. An iterator is
/// invalidated only when the corresponding element is deleted.

template <class T>
class LList {
public:
    struct BiDirectionalIterator {
        // Iterator traits
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        // Constructor
        explicit BiDirectionalIterator(Node<T>* ptr = nullptr)
        : current(ptr) {}

        // Dereference operators
        reference operator*()  const;
        pointer   operator->() const;

        // Increment/decrement operators
        BiDirectionalIterator& operator++();
        BiDirectionalIterator  operator++(int ignored);
        BiDirectionalIterator& operator--();
        BiDirectionalIterator  operator--(int ignored);

        // Equality/Inequality comparison operators
        bool operator==(const BiDirectionalIterator& other) const;
        bool operator!=(const BiDirectionalIterator& other) const;

        Node<T>* current;  ///< pointer to Node encapsulated by struct
    };

    // types
    using value_type       = T;
    using reference        = value_type&;
    using const_reference  = const value_type&;
    using size_type        = std::size_t;
    using difference_type  = std::ptrdiff_t;
    using iterator         = BiDirectionalIterator;
    using const_iterator   = const iterator;

    // construct/copy/destroy
    /// Constructs empty list
    LList() : head(nullptr), tail(nullptr), count(0) {}

    /// Copy constructor. Constructs the list with the copy of the contents
    /// of other.
    /// @param other Another LList object to copy from.
    LList(const LList& other);

    /// Move constructor for the LList Class. Efficiently transfers
    /// Ownership of resourses between LList objects.
    ///
    /// @param other The LList to be moved.
    LList(LList&& other);

    /// Creates and Initializes a list from values provided by user.
    /// @param ilist List of values provided by user.
    /// @example LList<int> foo({node1, node2, node3});
    LList(std::initializer_list<T> ilist);

    /// Destructs the list. The used storage is deallocated.
    virtual ~LList();

    // assignment
    /// Copy assigmment operator for the LList class.
    /// Copies the contents of one LList into another.
    ///
    /// @param other The LList to be copied.
    /// @return A reference to the updated LList.
    LList& operator=(const LList& other);

    /// Move assignment operator for the LList class.
    /// Efficiently moves the contents of one LList into another.
    ///
    /// @param other The LList to be moved.
    /// @return A reference to the updated LList.
    LList& operator=(LList&& other);

    /// Initialize assignment operator for the LList class.
    /// Initializes list with value provided.
    ///
    /// @param ilist Provided values
    /// @return A list inilialized with values provided.
    LList& operator=(std::initializer_list<T> ilist);

    // iterators
    /// Returns a BiDirectional iterator to the first element of the vector.
    /// @return iterator to the first element.
    iterator       begin() noexcept;
    const_iterator begin() const noexcept;

    /// Returns a BiDirectional iterator to the last element of the vector.
    /// @return iterator to the last element.
    iterator       end() noexcept;
    const_iterator end() const noexcept;

    // capacity
    /// Checks if the LList has no elements, i.e. whether head == nullptr.
    /// @return True if the list is empty, otherwise false.
    bool empty() const noexcept {return begin() == end(); }

    /// Checks the amount of elements the list has
    /// @return Number of elements in list
    size_type size() const noexcept { return count; }

    // element access
    /// Returns a reference to the first element in the list.
    /// @note Calling empty list will throw an exemption
    /// @return Reference to the first element.
    reference       front();
    const_reference front() const;

    /// Returns a reference to the last element in the list.
    /// @note Calling empty list will throw an exemption
    /// @return Reference to the last element.
    reference       back();
    const_reference back() const;

    // modifiers
    /// Appends given value to front of containter
    /// @post Element is appended to front of container
    /// @param value Value to be appended
    void     push_front(const T& value);

    /// Deletes head element
    /// @post First element is removed
    void     pop_front();

    /// Appends given value to back of containter
    /// @post Element is appended to back of container
    /// @param value Value to be appended
    void     push_back(const T& value);

    /// Deletes tail element
    /// @post Last element is removed
    void     pop_back();

    /// Inserts Given value into given position
    /// @note Invalid Position will cause an exemption out_of_range
    /// @param position Position where value will be inserted
    /// @param value Value to be appended
    iterator insert(const_iterator position, const T& value);

    /// deletes given value from given position
    /// @note Invalid Position will cause an exemption out_of_range
    /// @param position Position where value will be erased
    iterator erase(const_iterator position);

    /// Swaps two nodes
    /// @param other Another LList object
    void     swap(LList& other);

    /// Clears list, ready to be reused
    void     clear() noexcept;

private:
    Node<T>*  head;
    Node<T>*  tail;
    size_type count;
};

///----------------------------------------------------------------------------
///                  BIDIRECTIONAL ITERATOR STRUCT FUNCTIONS
///----------------------------------------------------------------------------

// Operator Overloads

template <class T>
typename LList<T>::BiDirectionalIterator::reference
         LList<T>::BiDirectionalIterator::operator*() const {
    return current->data;
}

template <class T>
typename LList<T>::BiDirectionalIterator::pointer
         LList<T>::BiDirectionalIterator::operator->() const {
    return &(current->data);
}

template <class T>
typename LList<T>::BiDirectionalIterator&
         LList<T>::BiDirectionalIterator::operator++() {
    current = current->next;
    return *this;
}

template <class T>
typename LList<T>::BiDirectionalIterator
         LList<T>::BiDirectionalIterator::operator++(int) {
    BiDirectionalIterator iter = *this;
    ++*this;
    return iter;
}

template <class T>
typename LList<T>::BiDirectionalIterator&
         LList<T>::BiDirectionalIterator::operator--() {
    current = current->prev;
    return *this;
}

template <class T>
typename LList<T>::BiDirectionalIterator
         LList<T>::BiDirectionalIterator::operator--(int) {
    BiDirectionalIterator iter = *this;
    current = current->prev;
    return iter;
}

template <class T>
bool LList<T>::BiDirectionalIterator::operator==(const BiDirectionalIterator&
                                                                  other) const {
    return current == other.current;
}

template <class T>
bool LList<T>::BiDirectionalIterator::operator!=(const BiDirectionalIterator&
                                                                  other) const {
    return current != other.current;
}

///----------------------------------------------------------------------------
///                           LLIST CLASS FUNCTIONS
///----------------------------------------------------------------------------

// COPY CONSTRUCTOR
template <class T>
LList<T>::LList(const LList& other) : LList<T>() {
    for (const auto& item : other) {
        push_back(item);
    }
}

// MOVE CONSTRUCTOR
template <class T>
LList<T>::LList(LList&& other) {
    head = std::exchange(other.head, nullptr);
    tail = std::exchange(other.tail, nullptr);
    count = std::exchange(other.count, 0);
}

// INITIALIZER
template <class T>
LList<T>::LList(std::initializer_list<T> ilist) : LList<T>() {
    for (const auto& item : ilist) {
        push_back(item);
    }
}

// DESTRUCTOR
template <class T>
LList<T>::~LList() {
    Node<T>* temp;             // pointer to delete the node

    while (head != nullptr) {  // delete entire list
        temp = head;           // assign temp to first
        head = head->next;     // assign first to next node
        delete temp;           // delete the node
    }

    tail = nullptr;
    count = 0;
}

// Assignment Operator Overloads

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& other) {
    if (this != &other) {  // prevent self-assignment
        LList<T> temp(other);
        this->swap(temp);
    }
    return *this;
}

template <class T>
LList<T>& LList<T>::operator=(LList<T>&& other) {
    if (this != &other) {  // prevent self-assignment
        clear();
        head = std::exchange(other.head, nullptr);
        tail = std::exchange(other.tail, nullptr);
        count = std::exchange(other.count, 0);
    }

    return *this;
}

template <class T>
LList<T>& LList<T>::operator=(std::initializer_list<T> ilist) {
    LList<T> temp(ilist);
    this->swap(temp);
    return *this;
}

// Iterators

template <class T>
typename LList<T>::iterator LList<T>::begin() noexcept {
    return iterator(head);
}

template <class T>
typename LList<T>::const_iterator LList<T>::begin() const noexcept {
    return iterator(head);
}

template <class T>
typename LList<T>::iterator LList<T>::end() noexcept {
    return iterator(nullptr);
}

template <class T>
typename LList<T>::const_iterator LList<T>::end() const noexcept {
    return iterator(nullptr);
}

// element access

template <class T>
typename LList<T>::reference LList<T>::front() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    return head->data;
}

template <class T>
typename LList<T>::const_reference LList<T>::front() const {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    return head->data;
}

template <class T>
typename LList<T>::reference LList<T>::back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail->data;
}

template <class T>
typename LList<T>::const_reference LList<T>::back() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail->data;
}
// modifiers

template <class T>
void LList<T>::push_front(const T& value) {
    Node<T>* new_node = new Node<T>(value, nullptr, head);

    if (empty()) {
        tail = new_node;
    } else {
        head->prev = new_node;
    }

    head = new_node;

    ++count;
}

template <class T>
void LList<T>::pop_front() {
    if (!empty()) {
        Node<T>* temp = head;

        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete temp;

        --count;
    }
}

template <class T>
void LList<T>::push_back(const T& value) {
    Node<T>* new_node = new Node<T>(value, tail, nullptr);

    if (empty()) {
        head = new_node;
    } else {
        tail->next = new_node;
    }

    tail = new_node;

    ++count;
}

template <class T>
void LList<T>::pop_back() {
    if (!empty()) {
        Node<T>* temp = tail;

        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete temp;

        --count;
    }
}

template <class T>
typename LList<T>::iterator LList<T>::insert(const_iterator position, const T& value) {
    Node<T>* new_node {};

    if (position == end()) {
        push_back(value);
        new_node = tail;
    } else {
        Node<T>* current = position.current;

        new_node = new Node<T>(value, current->prev, current);

        if (current->prev != nullptr) {
            current->prev->next = new_node;
        } else {
            head = new_node;
        }

        current->prev = new_node;

        if (current == tail) {
            tail = new_node->next;
        }

        ++count;
    }

    return iterator(new_node);
}

template <class T>
typename LList<T>::iterator LList<T>::erase(const_iterator position) {
    if (position == end()) {
        throw std::invalid_argument("cannot erase end() iterator");
    }

    Node<T>* current = position.current;  // direct access to node address
    iterator next_node;          // iterator to node following erased node

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        head = current->next;  // erase first
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;  // erase last
    }

    next_node = iterator(current->next);

    delete current;

    --count;

    return next_node;
}

template <class T>
void LList<T>::swap(LList& other) {
     // Swap heads
    Node<T>* tempHead = head;
    head = other.head;
    other.head = tempHead;

    // Swap tails
    Node<T>* tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;

    // Swap counts
    size_t tempCount = count;
    count = other.count;
    other.count = tempCount;
}

template <class T>
void LList<T>::clear() noexcept {
    while (!empty()) {
        pop_front();
    }
}

#endif // LLIST_HPP
