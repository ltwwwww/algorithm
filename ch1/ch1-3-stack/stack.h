#pragma once
#include <string>
#include <iostream>
#include <memory>
template <class T>

class Stack{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    Stack() : data(0), avail(0), limit(0) {};
    Stack(size_type cap = 0) { create(cap);}
    Stack(const Stack&);
    Stack& operator=(const Stack&);
    ~Stack(){ uncreate(); }
    bool isEmpty() { return avail == data;}
    size_type size() { return avail - data; }
    void push(const T& item) { 
        if(avail == limit){
            grow();
        }
        unchecked_append(item);
    }
    T pop() { 
        T item = *(avail - 1);
        alloc.destroy(--avail);
        // a[n] = NULL;
        return item;
    }
private:
    iterator data;
    iterator avail;
    iterator limit;

    std::allocator<T> alloc;
    void create(size_type);
    void uncreate();
    void grow();
    void unchecked_append(const T&);
    // void clone();
};

template <class T>
void Stack<T>::create(size_type n){
    data = avail = alloc.allocate(n);
    limit = data + n;
}

template <typename T>
Stack<T>::Stack(const Stack& rhs){
    data = alloc.allocate(rhs.limit - rhs.data);
    avail = limit = std::uninitialized_copy(rhs.data, rhs.avail, data);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& rhs){
    if(this != &rhs){
        uncreate();
        data = alloc.allocate(rhs.limit - rhs.data);
        avail = limit = std::uninitialized_copy(rhs.data, rhs.avail, data);
    }
    return *this;
}

template <typename T>
void Stack<T>::uncreate(){
    if(data){
        iterator it = avail;
        while(it != data){
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    }
    data = avail = limit = 0;
}

template <class T>
void Stack<T>::grow(){
    size_type new_size = std::max( 2 * (limit - data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <typename T>
void Stack<T>::unchecked_append(const T& item){
    alloc.construct(avail++, item);
}