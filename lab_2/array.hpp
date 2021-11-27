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
        int type_;
    public:
        const static int kReverceType = -1;
        const static int kNotReverceType = 1;
    private:
        Array* arr_;
    public:
        Iterator(Array *a, int type);
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


// ====================================================
//                Iterator definitions
// ====================================================

template <typename T>
Array<T>::Iterator::Iterator(Array *a, int type)
    : current_value_(a->at(0))
    , type_(type)
    , arr_(a) {
        if (type_ == Iterator::kReverceType)
            current_index_ = a->size() - 1;
        else
            current_index_ = 0;
}

template <typename T>
T& Array<T>::Iterator::get() const {
    return arr_->at(current_index_);
}

template <typename T>
void Array<T>::Iterator::set(const T& value) {
    arr_[current_index_] = value;
}

template <typename T>
void Array<T>::Iterator::next() {
    current_index_ += type_;
}

template <typename T>
bool Array<T>::Iterator::hasNext() const {
    if (type_ == Iterator::kNotReverceType)
        return !(current_index_ == arr_->size() - 1);
    else
        return !(current_index_ == 0);
}

template <typename T>
typename Array<T>::Iterator Array<T>::iterator(){
    Iterator it(this, Array<T>::Iterator::kNotReverceType);
    return it;
}

template <typename T>
typename Array<T>::Iterator Array<T>::reverseIterator(){
    Iterator it(this, Array<T>::Iterator::kReverceType);
    return it;
}
// ====================================================
//                  Array defenitions
// ====================================================

template <typename T>
void Array<T>::extend() {
    T* new_buffer;
    capacity_ = capacity_ * 2;
    new_buffer = static_cast<T*>(malloc(sizeof(T) * capacity_));
    for (int i = 0; i < count_; i++){
        T& current_value = at(i);
        if (std::is_move_constructible<T>::value) {
            new(new_buffer + i) T(std::move_if_noexcept(current_value));
        } else {
            new(new_buffer + i) T(current_value);
        }
    }
    for (auto it = this->iterator(); it.hasNext(); it.next()) it.get().~T();
    free(buffer_);
    buffer_ = new_buffer;
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
    for (auto it = this->iterator(); it.hasNext(); it.next()) it.get().~T();
    free(buffer_);
}

template <typename T>
int Array<T>::insert(const T& value) {
    if (count_ >= capacity_) {
        extend();
    }
    if (std::is_move_constructible<T>::value) {
        new(buffer_ + count_) T(std::move_if_noexcept(value));
    } else {
        new(buffer_ + count_) T(value);
    }
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
