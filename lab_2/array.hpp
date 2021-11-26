//
//  array.hpp
//  lab_2
//
//  Created by Евгений Курятов on 18.11.2021.
//

#ifndef array_hpp
#define array_hpp

#include <stdio.h>
#include <iostream>
#include <utility>
#include "array.hpp"

const int kDefultArrraySize = 8;

template <typename T>
class Array final {
private:
    T* buffer_;
    int count_;
    int capacity_;
private:
    void extend();
public:
    Array();
    Array(int capacity);
    ~Array();
    
    class Iterator {
    private:
        int current_index_;
        T& current_value_;
    public:
        Iterator(Array *a);
        T& get() const;
        void set(const T& value);
        void next();
        bool hasNext() const;
    };
    
    int insert(const T& value);
    int insert(int index, const T& value);
    
    
    void remove(int index);
    
    T& at(int index);
    const T& operator[](int index) const;
    T& operator[](int index);
    
    int size() const;
    
    void printArrayInfo();
    
    Iterator iterator();
//    ConstIterator iterator() const;
    
    Iterator reverseIterator();
//    ConstIterator reverseIterator() const;
};

template <typename T>
Array<T>::Iterator::Iterator(Array *a) {
    current_index_ = 0;
    current_value_ = a->at(current_index_);
}

template <typename T>
T& Array<T>::Iterator::get() const {
    return Array.this.at(current_index_);
}

template <typename T>
void Array<T>::extend() {
    T* new_buffer;
    capacity_ = capacity_ * 2;
    new_buffer = static_cast<T*>(malloc(sizeof(T) * capacity_));
    for (int i = 0; i < count_; i++){
        T& current_value = at(i);
        if (std::is_move_constructible<T>::value) {
            new_buffer[i] = std::move_if_noexcept(current_value);
        } else {
            new_buffer[i] = current_value;
        }
    }
    free(buffer_);
    buffer_ = new_buffer;
//    delete [] buffer_;
}

template <typename T>
Array<T>::Array() {
    capacity_ = kDefultArrraySize;
    buffer_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
    count_ = 0;
}

template <typename T>
Array<T>::Array(int capcity) {
    capacity_ = capcity;
    buffer_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
    count_ = 0;
}

template <typename T>
Array<T>::~Array() {
//    delete [] buffer_;
    free(buffer_);
}

template <typename T>
int Array<T>::insert(const T& value) {
    if (count_ >= capacity_) {
        extend();
    }
    *(buffer_ + count_) = value;
    count_ += 1;
    return count_;
}

template <typename T>
int Array<T>::size() const {
    return count_;
}

template <typename T>
T& Array<T>::at(int index){
    return buffer_[index];
}

template <typename T>
const T& Array<T>::operator[](int index) const {
    return at(index);
}

template <typename T>
T& Array<T>::operator[](int index) {
    return at(index);
}

template <typename T>
void Array<T>::printArrayInfo(){
    std::cout << "Length: " << count_ << "\n";
    std::cout << "Capacity: " << capacity_ << "\n";
    std::cout << "Array content: ";
    for (int i = 0; i < count_; i++) {
        std::cout << at(i) << " ";
    }
    std::cout << "\n";
    std::cout << "------------------\n";
}

#endif /* array_hpp */
