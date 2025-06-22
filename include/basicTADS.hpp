#ifndef TADS_HPP
#define TADS_HPP

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* dataArray;
    int size;
    int capacity;
    

public:
// O tamanho máximo da pilha sempre será declarado aqui, uma vez que isso representa o tamanho máximo do armazem.
// Por questão de seguir a abstratabilidade do TAD, decidi implementar resize também, mas não será utilizado por padrão no código.
    Stack(int initialCapacity); 
    
    void resize(int newCapacity);
    void push(const T& data); // Adiciona um novo pacote no topo da pilha
    T pop(); // Remove o último colocado
    T getHead() const; // Retorna o pacote no topo da pilha

    void clear(); // Limpa a pilha, removendo todos os pacotes
    ~Stack();
};

// Lista templatizada implementada como lista circular
template <typename T>
class Queue { 
private:
    T* dataArray;
    int first; // -- Primeiro da Fila
    int last; // -- Último da Fila
    int size;
    int capacity;
    
public:

    Queue(int initialCapacity);
    void resize(int newCapacity);
    void enqueue(const T& data);
    T dequeue();
    T getFirstInLine() const;
    int getSize();

    void clear();
    ~Queue();

};

template<typename T>
class List{
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    int listSize;

public:
    List();
    
    void pushFront(const T& value);
    void pushBack(const T& value);
    void removeFront();
    bool search(const T& value) const;
    T popHead();
    T& front() const;
    T& get(int i) const;
    bool isEmpty() const;
    int getSize() const;
    void clear();

    ~List();

};

#endif