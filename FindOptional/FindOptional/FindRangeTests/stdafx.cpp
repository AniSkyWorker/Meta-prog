// stdafx.cpp : source file that includes just the standard includes
// adapters_tests.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
#define BOOST_TEST_NO_MAIN 
// подключаем реализацию boost test
#pragma warning (push, 3)
#pragma warning (disable:4702)
#include <boost/test/included/unit_test.hpp>
#pragma warning (pop)