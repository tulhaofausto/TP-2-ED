#include "minHeap.hpp"
#include "event.hpp"

template <typename T>
MinHeap<T>::MinHeap(size_t initialCapacity) : size(0), capacity(initialCapacity) {
    if (capacity == 0) { // Garante uma capacidade mínima para evitar alocação de 0 bytes
        capacity = 1;
    }
    heapArray = new T[capacity];
}

template <typename T>
MinHeap<T>::~MinHeap() {
    delete[] heapArray;
}

template <typename T>
void MinHeap<T>::resize() {
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
    T* newArray = new T[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newArray[i] = heapArray[i];
    }
    delete[] heapArray;
    heapArray = newArray;
    capacity = newCapacity;
}

template <typename T>
size_t MinHeap<T>::getParentIndex(size_t childIndex) const {
    return (childIndex - 1) / 2;
}

template <typename T>
size_t MinHeap<T>::getLeftChildIndex(size_t parentIndex) const {
    return 2 * parentIndex + 1;
}

template <typename T>
size_t MinHeap<T>::getRightChildIndex(size_t parentIndex) const {
    return 2 * parentIndex + 2;
}

template <typename T>
bool MinHeap<T>::hasParent(size_t Index) const {
    return Index > 0;
}

template <typename T>
bool MinHeap<T>::hasLeftChild(size_t Index) const {
    return getLeftChildIndex(Index) < size;
}

template <typename T>
bool MinHeap<T>::hasRightChild(size_t Index) const {
    return getRightChildIndex(Index) < size;
}

template <typename T>
void MinHeap<T>::swap(size_t Index1, size_t Index2) {
    T temp = heapArray[Index1];
    heapArray[Index1] = heapArray[Index2];
    heapArray[Index2] = temp;
}

template <typename T>
void MinHeap<T>::heapifyUp(size_t Index) {
    while (hasParent(Index) && heapArray[getParentIndex(Index)] > heapArray[Index]) {
        swap(getParentIndex(Index), Index);
        Index = getParentIndex(Index);
    }
}

template <typename T>
void MinHeap<T>::heapifyDown(size_t Index) {
    size_t smallestChildIndex = Index;

    while (hasLeftChild(Index)) {
        size_t leftChildIndex = getLeftChildIndex(Index);
        size_t rightChildIndex = getRightChildIndex(Index);

        if (heapArray[leftChildIndex] < heapArray[smallestChildIndex]) {
            smallestChildIndex = leftChildIndex;
        }

        if (hasRightChild(Index) && heapArray[rightChildIndex] < heapArray[smallestChildIndex]) {
            smallestChildIndex = rightChildIndex;
        }

        if (smallestChildIndex == Index) {
            break;
        } else {
            swap(Index, smallestChildIndex);
            Index = smallestChildIndex;
        }
    }
}

template <typename T>
void MinHeap<T>::push(const T& item) {
    if (size == capacity) {
        resize();
    }
    heapArray[size] = item;
    size++;
    heapifyUp(size - 1);
}

template <typename T>
T MinHeap<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Heap is empty. Cannot pop from an empty heap.");
    }
    T item = heapArray[0];
    heapArray[0] = heapArray[size - 1];
    size--;
    if (!isEmpty()) {
        heapifyDown(0);
    }
    return item;
}

template <typename T>
void MinHeap<T>::printInOrder() {
    // Cria uma cópia do heap para não alterar o original
    MinHeap<T> tempHeap(*this);
    while (!tempHeap.isEmpty()) {
        std::cout << tempHeap.pop() << " ";
    }
    std::cout << std::endl;
}

template <typename T>
const T& MinHeap<T>::top() const {
    if (isEmpty()) {
        throw std::out_of_range("Heap is empty. Cannot get top from an empty heap.");
    }
    return heapArray[0];
}

template <typename T>
bool MinHeap<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
size_t MinHeap<T>::getSize() const {
    return size;
}

template <typename T>
void MinHeap<T>::clear() {
    delete[] heapArray;
    capacity = 10;
    size = 0;
    heapArray = new T[capacity]; 
}

template class MinHeap<Event*>;
template class MinHeap<Event>;