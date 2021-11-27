//
//  main.cpp
//  lab_2
//
//  Created by Евгений Курятов on 18.11.2021.
//

#include <iostream>
#include "array.hpp"

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

int main() {
    Array<TestClass> a;
    for (int i = 0; i < 10; ++i) {
        TestClass te(i, false);
        a.insert(te);
    }
    for (int i = 0; i < a.size(); ++i)
        a[i].value_ *= 2;
    a.printArrayInfo();
    for (auto it = a.iterator(); it.hasNext(); it.next())
      std::cout << it.get() << std::endl;
    
    Array<int> b;
    for (int i = 0; i < 10; ++i) {
        b.insert(i);
    }
    for (int i = 0; i < b.size(); ++i)
        b[i] *= 2;
    b.printArrayInfo();
    for (auto it = b.reverseIterator(); it.hasNext(); it.next())
      std::cout << it.get() << std::endl;
    return 0;
}
