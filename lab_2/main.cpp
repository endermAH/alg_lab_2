//
//  main.cpp
//  lab_2
//
//  Created by Евгений Курятов on 18.11.2021.
//

#include <iostream>
#include "array.hpp"

int main() {
    Array<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    a.printArrayInfo();
    return 0;
}
