#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <iostream>
#include <stdexcept> 

template <typename T>
class MinHeap {
private:
    T* heapArray;
    size_t capacity;
    size_t size;

    size_t getParentIndex(size_t childIndex) const;
    size_t getLeftChildIndex(size_t parentIndex) const;
    size_t getRightChildIndex(size_t parentIndex) const;

    bool hasParent(size_t index) const;
    bool hasLeftChild(size_t index) const;
    bool hasRightChild(size_t index) const;

    void swap(size_t indexA, size_t indexB);

    void heapifyUp(size_t index);
    void heapifyDown(size_t index);

    void resize();

public:
    MinHeap(size_t initialCapacity = 10);

    void push(const T& item);
    T pop();
    const T& top() const;

    void printInOrder();
    bool isEmpty() const;
    size_t getSize() const;
    void clear();

    ~MinHeap();
};

#endif