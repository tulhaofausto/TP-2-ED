#include "basicTADS.hpp"
#include "package.hpp"
#include "depot.hpp"

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
template class Queue<int>;
template class Queue<bool>;

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