#include "stack.hpp"

template <typename T>
Stack<T>::Stack(int initialCapacity) : size(0), capacity(initialCapacity) {
    packages = new T[capacity];
}

/// @brief Ajusta a capacidade da pilha (deve ser utilizado para aumentar).
/// @param newCapacity Capacidade nova da pilha.
template <typename T>
void Stack<T>::resize(int newCapacity) {
    T* newPackages = new T[newCapacity]; //Cria um novo array de pacotes com a nova capacidade 
    for (int i = 0; i < size; ++i) {                 //Copia os pacotes existentes para o novo array
        newPackages[i] = packages[i];
    }

    delete[] packages; //Libera o antigo
    packages = newPackages; //Atualiza o ponteiro para o novo array
    capacity = newCapacity; //Atualiza a capacidade
}

/// @brief Adiciona um novo pacote no topo da pilha.
/// @param package Pacote a ser adicionado.
template <typename T>
void Stack<T>::push(const T& package) {

/*  //Resize caso seja necessário de acordo com o VPL ou a implementação do projeto.
    if (size == capacity) {
        resize(capacity * 2); 
    }
*/
    if (size >= capacity) {
        throw std::overflow_error("O armazem esta cheio. Nao e possivel adicionar mais pacotes.");
    }  
    
    packages[size++] = package; // Adiciona o pacote no topo da pilha e aumenta o tamanho

}

/// @brief Remove o pacote do topo da pilha.
/// @details O pacote não é liberado, mas pode ser sobrescrito na próxima inserção.
/// @return Pacote removido do topo da pilha.
template <typename T>
T Stack<T>::pop() {
    if (size == 0) {
        throw std::underflow_error("A pilha esta vazia. Nao e possivel remover pacotes.");
    }
    
    return packages[--size]; // Retorna o pacote do topo e diminui o tamanho
}

/// @brief Obtém o pacote no topo da pilha sem removê-lo.
/// @return Pacote no topo da pilha.
template <typename T>
T Stack<T>::getHead() const {
    if (size == 0) {
        throw std::underflow_error("A pilha esta vazia. Nao e possivel obter o pacote do topo.");
    }
    
    return packages[size - 1]; // Retorna o pacote do topo sem removê-lo
}

/// @brief Muda o size para 0, efetivamente limpando a pilha.
template <typename T>
void Stack<T>::clear() {
    size = 0; // Reseta o tamanho da pilha, efetivamente limpando-a
              // Não é necessário liberar a memória dos pacotes, pois eles serão sobrescritos na próxima inserção
}

/// @brief Destrutor da classe Stack.
template <typename T>
Stack<T>::~Stack() {
    delete[] packages; // Libera a memória alocada para os pacotes
}

template class Stack<Package>; // Instancia a classe Stack para o tipo Package
template class Stack<Depot>; // Instancia a classe Stack para o tipo depotStack