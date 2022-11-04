#pragma once

#ifdef NDEBUG

#define RenderAssert(expression) ((void)0)

#else

#include <iostream>
#include <string_view>
#include <cassert>
#define RenderAssert(expression, msg) (void)((!!(expression)) || (wprintf(L"Assert triggered:\t%S\n%s %i\n",msg, _CRT_WIDE(__FILE__), (unsigned)(__LINE__)))< 0); assert(expression);                                                               
#define NonBreakingRenderAssert(expression, msg) (void)((!!(expression)) || (wprintf(L"Assert triggered:\t%S\n%s %i\n",msg, _CRT_WIDE(__FILE__), (unsigned)(__LINE__)))< 0);                                                               

#endif