#ifndef STACK_HPP
#define STACK_HPP

#include "package.hpp"
#include <stdexcept>

template <typename T>
class Stack {
private:
    T* packages;
    int size;
    int capacity;
    void resize(int newCapacity);

public:
// O tamanho máximo da pilha sempre será declarado aqui, uma vez que isso representa o tamanho máximo do armazem.
// Por questão de seguir padrão, decidi implementar resize também, mas não será utilizado por padrão no código.
    Stack(int initialCapacity); 

    void push(const T& package); // Adiciona um novo pacote no topo da pilha
    T pop(); // Remove o último colocado
    T getHead() const; // Retorna o pacote no topo da pilha

    void clear(); // Limpa a pilha, removendo todos os pacotes
    ~Stack();
};

#endif