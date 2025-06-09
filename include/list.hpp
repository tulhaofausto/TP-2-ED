#ifndef GRAPH_HPP
#define GRAPH_HPP

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
    T& front() const;
    bool isEmpty() const;
    int size() const;
    void clear();

    ~List();

};

#endif
