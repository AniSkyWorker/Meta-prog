#include "stdafx.h"
#include <functional>
#include <iostream>
#include "MovableFunction.h"
#include <memory>
using namespace movable_function;

int main()
{
    auto lambda = [](int x) { return x; };
    using lambdaType = decltype(lambda);

    MovableFunction<int(int i, int j)> func = [](int i, int j) {
        std::cout << i + j;
        return 0;
    };
    func(5, 3);
    return 0;
}

