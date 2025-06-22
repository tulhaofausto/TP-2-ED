#include "list.hpp"
#include "depot.hpp"
#include <stdexcept>

template<typename T>
List<T>::List() : head(nullptr), listSize(0) {}

/// @brief Adiciona um elemento no início da lista
/// @tparam Dado a adicionar
template<typename T>
void List<T>::pushFront(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    ++listSize;
}

/// @brief Adiciona um elemento no final da lista
/// @details Caso a lista esteja vazia, o novo nó se torna o head.
/// @param value 
template<typename T>
void List<T>::pushBack(const T& value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }
    listSize++;
}

/// @brief Remove o primeiro elemento da lista
template<typename T>
void List<T>::removeFront() {
    if (isEmpty())
        throw std::underflow_error("Lista vazia.");
    Node* temp = head;
    head = head->next;
    delete temp;
    listSize--;
}

template<typename T>
T List<T>::popHead() {
    if (isEmpty())
        throw std::underflow_error("Lista vazia.");
    Node* temp = head;
    T value = temp->data;
    head = head->next;
    delete temp;
    listSize--;
    return value;
}

/// @brief Retorna o primeiro elemento da lista
template<typename T>
T& List<T>::front() const {
    if (isEmpty())
        throw std::underflow_error("Lista vazia.");
    return head->data;
}

template<typename T>
bool List<T>::search(const T& value) const {
    Node* current = this->first;
    while (current != nullptr) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

template<typename T>
T& List<T>::get(int i) const{

    if (i > listSize)
        throw std::out_of_range("indice nao existe na lista");

    int j = 0;
    Node* aux = this->first;

    for(j = 0; j < i; j++){
        aux = aux->next;
    }

    return aux->data;
}

/// @brief Retorna 1 caso a lista esteja vazia.
template<typename T>
bool List<T>::isEmpty() const {
    return head == nullptr;
}

/// @brief Retorna o tamanho da lista
template<typename T>
int List<T>::getSize() const {
    return listSize;
}

/// @brief Limpa a lista, removendo todos os elementos
template<typename T>
void List<T>::clear() {
    while (!isEmpty()) {
        removeFront();
    }
}

/// @brief Destrutor da lista
template<typename T>
List<T>::~List() {
    clear();
}

template class List<Depot>; 
template class List<Depot*>;
template class List<bool>;
template class List<int>;