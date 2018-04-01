#include "stdafx.h"
#include "../FindOptional/FindOptional.h"

struct SomeStruct
{
    int num;
};

BOOST_AUTO_TEST_SUITE(find_optional_tests)
BOOST_AUTO_TEST_CASE(can_find_element_in_int_range)
{
    const auto searched = 10;
    std::vector<int> numArray = { 1, 4, 6, 10, 11 };
    auto foundElem = range_find::FindOptional(numArray, [searched = searched](const auto& element){
        return element == searched;
    });

    BOOST_CHECK(foundElem);
    BOOST_CHECK_EQUAL(*foundElem, searched);
}

BOOST_AUTO_TEST_CASE(can_find_element_in_string_range)
{
    const auto searched = "spring";
    std::vector<std::string> numArray = { "mama", "papa", "decade", "summertime", "spring"};
    auto foundElem = range_find::FindOptional(numArray, [searched = searched](const auto& element){
        return element == searched;
    });

    BOOST_CHECK(foundElem);
    BOOST_CHECK_EQUAL(*foundElem, searched);
}

BOOST_AUTO_TEST_CASE(can_find_element_in_string_range_when_range_const_rvalue)
{
    const auto searched = "spring";
    const std::vector<std::string> numArray = { "mama", "papa", "decade", "summertime", "spring" };
    auto foundElem = range_find::FindOptional(numArray, [searched = searched](const auto& element){
        return element == searched;
    });

    BOOST_CHECK(foundElem);
    BOOST_CHECK_EQUAL(*foundElem, searched);
}

BOOST_AUTO_TEST_CASE(can_find_element_in_string_range_when_range_lvalue)
{
    SomeStruct first{ 1 };
    SomeStruct second{ 2 };
    SomeStruct third{ 3 };

    SomeStruct searchedStruct{ 1 };
    std::vector<SomeStruct*> numArray = { &first, &second, &third };

    auto foundElem = range_find::FindOptional(numArray, [searched = searchedStruct](const auto& element){
        return element->num == searched.num;
    });

    BOOST_CHECK(foundElem);
    BOOST_CHECK_EQUAL((*foundElem)->num, searchedStruct.num);
}

BOOST_AUTO_TEST_CASE(can_find_element_in_string_range_when_predicate_move_capture_lambda)
{
    struct SomeStruct {
        int num;
    };

    SomeStruct first{ 1 };
    SomeStruct second{ 2 };
    SomeStruct third{ 3 };

    SomeStruct searchedStruct{ 3 };
    std::vector<SomeStruct*> numArray = { &first, &second, &third };

    auto foundElem = range_find::FindOptional(numArray, [searched = std::move(searchedStruct)](const auto& element){
        return element->num == searched.num;
    });

    BOOST_CHECK(foundElem);
    BOOST_CHECK_EQUAL((*foundElem)->num, searchedStruct.num);
}
BOOST_AUTO_TEST_SUITE_END()