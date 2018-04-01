#pragma once
#include <functional>
#include <boost\optional.hpp>

namespace range_find
{
template<typename Range, typename Predicate>
decltype(auto) FindOptional(Range&& range, Predicate&& predicate)
{
    boost::optional<std::remove_cv_t<std::remove_reference_t<decltype(*range.begin())>>> result;
    for (auto&& element : range)
    {
        if (std::invoke(std::forward<Predicate>(predicate), element))
        {
            result = element;
            break;
        }
    }
    return result;
}
}