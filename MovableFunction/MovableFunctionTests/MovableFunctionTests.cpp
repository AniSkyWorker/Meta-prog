#include "stdafx.h"
#include "../MovableFunction/MovableFunction.h"

using movable_function::MovableFunction;

namespace test_functors
{
void AdditionProcedure(int &number, int addition)
{
    number = number + addition;
}

int AdditionFunction(int number, int addition)
{
    return number + addition;
}

struct AdditionOperator
{
    int operator()(int num, int addition) const
    {
        return num + addition;
    }
};

class Number
{
public:
    Number(int num) : m_value(num)
    {}

    void Add(int addition)
    {
        m_value += addition;
    }

    int GetValue() const
    {
        return m_value;
    }

private:
    int m_value = 0;
};
}

BOOST_AUTO_TEST_SUITE(MovableFunction_tests)
using namespace test_functors;
BOOST_AUTO_TEST_CASE(init_by_procedure)
{
    MovableFunction<void(int&, int)> func(AdditionProcedure);
    int num = 0;
    func(num, 5);
    BOOST_CHECK_EQUAL(num, 5);
}

BOOST_AUTO_TEST_CASE(init_by_function)
{
    MovableFunction<int(int, int)> func(AdditionFunction);
    const auto result = func(0, 5);
    BOOST_CHECK_EQUAL(result, 5);
}

BOOST_AUTO_TEST_CASE(init_by_lambda)
{
    bool called = false;
    MovableFunction<int(int, int)> func = [](int num, int addition) {
        return num + addition;
    };
    const auto result = func(0, 5);
    BOOST_CHECK_EQUAL(result, 5);
}

BOOST_AUTO_TEST_CASE(init_by_obj_functor)
{
    MovableFunction<int(int, int)> func({ AdditionOperator() });
    const auto result = func(0, 5);
    BOOST_CHECK_EQUAL(result, 5);
}

BOOST_AUTO_TEST_CASE(init_by_binded_functor)
{
    Number num(0);
    MovableFunction<void(int)> func(std::bind(&Number::Add, &num, std::placeholders::_1));
    func(5);
    BOOST_CHECK_EQUAL(num.GetValue(), 5);
}

BOOST_AUTO_TEST_CASE(init_by_movable_lambda)
{
    MovableFunction<int(int)> func = [numPtr = std::make_unique<int>(0)] (int addition){ 
        return *numPtr + addition; 
    };
    const auto result = func(5);
    BOOST_CHECK_EQUAL(result, 5);
}

BOOST_AUTO_TEST_CASE(throws_when_called_with_empty_functor)
{
    MovableFunction<void()> func;
    BOOST_REQUIRE_THROW(func(), std::bad_function_call);
}

BOOST_AUTO_TEST_SUITE_END()
