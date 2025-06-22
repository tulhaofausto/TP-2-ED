#ifndef LIST_HPP
#define LIST_HPP

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
