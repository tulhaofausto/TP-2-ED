#include "stack.hpp"

template <typename T>
Stack<T>::Stack(int initialCapacity) : size(0), capacity(initialCapacity) {
    dataArray = new T[capacity];
}

/// @brief Ajusta a capacidade da pilha (deve ser utilizado para aumentar).
/// @param newCapacity Capacidade nova da pilha.
template <typename T>
void Stack<T>::resize(int newCapacity) {
    T* newdataArray = new T[newCapacity]; //Cria um novo array de pacotes com a nova capacidade 
    for (int i = 0; i < size; ++i) {                 //Copia os pacotes existentes para o novo array
        newdataArray[i] = dataArray[i];
    }

    delete[] dataArray; //Libera o antigo
    dataArray = newdataArray; //Atualiza o ponteiro para o novo array
    capacity = newCapacity; //Atualiza a capacidade
}

/// @brief Adiciona um novo pacote no topo da pilha.
/// @param Data Pacote a ser adicionado.
template <typename T>
void Stack<T>::push(const T& Data) {

/*  //Resize caso seja necessário de acordo com o VPL ou a implementação do projeto.
    if (size == capacity) {
        resize(capacity * 2); 
    }
*/
    if (size >= capacity) {
        throw std::overflow_error("O armazem esta cheio. Nao e possivel adicionar mais pacotes.");
    }  
    
    dataArray[size++] = Data; // Adiciona o pacote no topo da pilha e aumenta o tamanho

}

/// @brief Remove o pacote do topo da pilha.
/// @details O pacote não é liberado, mas pode ser sobrescrito na próxima inserção.
/// @return Pacote removido do topo da pilha.
template <typename T>
T Stack<T>::pop() {
    if (size == 0) {
        throw std::underflow_error("A pilha esta vazia. Nao e possivel remover pacotes.");
    }
    
    return dataArray[--size]; // Retorna o pacote do topo e diminui o tamanho
}

/// @brief Obtém o pacote no topo da pilha sem removê-lo.
/// @return Pacote no topo da pilha.
template <typename T>
T Stack<T>::getHead() const {
    if (size == 0) {
        throw std::underflow_error("A pilha esta vazia. Nao e possivel obter o pacote do topo.");
    }
    
    return dataArray[size - 1]; // Retorna o pacote do topo sem removê-lo
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
    delete[] dataArray; // Libera a memória alocada para os pacotes
}

template class Stack<Package>; // Instancia a classe Stack para o tipo Package
template class Stack<Depot>; // Instancia a classe Stack para o tipo depotStack

/// @brief Fila implementada como fila circular
/// @tparam T 
/// @param initialCapacity 
template <typename T>
Queue<T>::Queue(int initialCapacity):capacity(initialCapacity), size(0), first(0), last(0){
    dataArray = new T[initialCapacity];

}

/// @brief Resize copia todos os valores para um vetor maior
/// @details Na implementação do TP não é utilizado mas é útil caso haja, por exemplo um aumento no tamanho do depósito ou coisas do tipo.
/// @tparam T 
/// @param newCapacity 
template <typename T>
void Queue<T>::resize(int newCapacity) {
    T* newdataArray = new T[newCapacity]; //Cria um novo array de pacotes com a nova capacidade 
    for (int i = 0; i < size; ++i) {                 //Copia os pacotes existentes para o novo array
        newdataArray[i] = dataArray[i];
    }

    delete[] dataArray; //Libera o antigo
    dataArray = newdataArray; //Atualiza o ponteiro para o novo array
    capacity = newCapacity; //Atualiza a capacidade
}

template <typename T>
void Queue<T>::enqueue(const T& data){

/*  Implementação com resize; Não será utilizada, mas pela abstração deixarei aqui
    if(size == capacity){
        resize(2*capacity);
    }
*/
    
    if(size == capacity){
        throw std::overflow_error("Fila cheia, impossivel enfileirar");
    }

    dataArray[last] = data;
    last = (last + 1) % this->capacity;
    size++;
    
}

template <typename T>
T Queue<T>::dequeue(){

    if(size == 0){
        throw std::underflow_error("Fila vazia. Impossivel desinfileirar");
    }

    T aux = dataArray[first];
    first = (first + 1) % this->capacity;
    size--;
    return aux;
}

template <typename T>
T Queue<T>::getFirstInLine() const{
    
    if(size == 0){
        throw std::underflow_error("Fila vazia. Nada a retornar")
    }

    return dataArray[first];
}

template <typename T>
int Queue<T>::getSize(){
    return this->size;
};

template <typename T>
void Queue<T>::clear(){
    delete[] dataArray;
}

template <typename T>
Queue<T>::~Queue(){
    this->clear();
}

template class Queue<Depot>;
template class Queue<Depot*>;
template class Queue<Package>;
