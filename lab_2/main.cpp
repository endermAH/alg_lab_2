//
//  main.cpp
//  lab_2
//
//  Created by Евгений Курятов on 18.11.2021.
//

#include <iostream>
#include "array.hpp"
#include "gtest/gtest.h"

class TestClass {
public:
    int value_;
    bool debug_;
    const int b = 3;
public:
    TestClass(int val, bool debug)
        : value_(val)
        , debug_(debug) {
        value_ = val;
        if (debug_) std::cout << "Constructed [" << value_ << "]\n";
    }
    ~TestClass(){
        if (debug_) std::cout << "Destructed [" << value_ << "]\n";
    }
};

std::ostream& operator<<(std::ostream& os, const TestClass& te)
{
    os << '[' << te.value_ << ']';
    return os;
}

TEST(TestInsert, InsertInt) {
    Array<int>* array = new Array<int>();
    for (int i = 0; i < 10; ++i) {
        int return_value = array->insert(i);
        ASSERT_EQ(return_value, i);
    }
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(array->at(i), i);
    }
    delete array;
}

TEST(TestInsert, InsertIntAt) {
    Array<int>* array = new Array<int>();
    for (int i = 0; i < 10; ++i) {
        array->insert(i);
    }
    int return_value = array->insert(2, 100);
    ASSERT_EQ(return_value, 2);
    ASSERT_EQ(array->at(0), 0);
    ASSERT_EQ(array->at(1), 1);
    ASSERT_EQ(array->at(2), 100);
    for (int i = 3; i < 11; ++i) {
        ASSERT_EQ(array->at(i), i-1);
    }
    delete array;
}

TEST(TestRemove, RemoveInt) {
    Array<int>* array = new Array<int>();
    for (int i = 0; i < 10; ++i) {
        array->insert(i);
    }
    array->remove(2);
    ASSERT_EQ(array->size(), 9);
    for (int i = 2; i < 9; ++i) {
        ASSERT_EQ(array->at(i), i+1);
    }
    delete array;
}

TEST(TestIterator, TestGetAndNext){
    Array<int>* array = new Array<int>();
    auto it = array->iterator();
    for (int i = 0; i < 10; ++i) {
        array->insert(i);
        ASSERT_EQ(array->at(i), it.get());
        it.next();
    }
    delete array;
}

TEST(TestIterator, TestConstructor){
    Array<int>* array = new Array<int>();
    for (int i = 0; i < 10; ++i) {
        array->insert(i);
    }
    auto it = array->iterator();
    ASSERT_EQ(it.get(), 0);
    delete array;
}

TEST(TestIterator, TestReverseConstructor){
    Array<int>* array = new Array<int>();
    for (int i = 0; i < 10; ++i) {
        array->insert(i);
    }
    auto it = array->reverseIterator();
    ASSERT_EQ(it.get(), 9);
    delete array;
}

TEST(TestIterator, TestSet){
    Array<int>* array = new Array<int>();
    for (int i = 0; i < 10; ++i)
        array->insert(i);
    auto it = array->iterator();
    for (int i = 0; i < 10; ++i) {
        array->insert(i);
        it.set(i * 2);
        ASSERT_EQ(array->at(i), i * 2);
        it.next();
    }
    delete array;
}

TEST(TestIterator, TestHasNext){
    Array<int>* array = new Array<int>();
    for (int i = 0; i < 10; ++i) {
        array->insert(i);
    }
    auto it = array->iterator();
    ASSERT_TRUE(it.hasNext());
    for (int i = 0; i < 9; ++i) {
        it.next();
    }
    ASSERT_FALSE(it.hasNext());
    delete array;
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
