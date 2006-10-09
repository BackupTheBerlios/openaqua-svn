#ifndef __CoaAssert_h__
#define __CoaAssert_h__



/**
@check compiler stuff

put a line like this in your code (outside the normal code and in a cpp file)
COA_ASSERT_COMPILE_CHECK(sizeof(int)==4);

This should work (means: it compiles an the code works)

try then a
COA_ASSERT_COMPILE_CHECK(sizeof(int)==3);

You will get a output like this
ication.o base/CoaApplication.cpp
base/CoaApplication.cpp:9: error: aggregate `CoaAssertCompileCheck<false>
   compile_time_assertion_failed_in_line_9' has incomplete type and cannot be
   defined
base/CoaApplication.cpp:9: error: storage size of `
   compile_time_assertion_failed_in_line_9' isn't known
make: *** [.obj/CoaApplication.o] Error 1


How does it work
The compiler creates a template object

*/


template<bool>
class CoaAssertCompileCheck;

template<>
class CoaAssertCompileCheck<true>
{
};



#if defined(__GNUC__)
#define _COA_ATTRIBUTE_UNUSED __attribute__ ((unused))
#else
#define _COA_ATTRIBUTE_UNUSED
#endif


//The Macro itself
#define COA_ASSERT_COMPILE_CHECK(condition) _CB_ASSERT_CT_1(condition, __LINE__)


//makes a integer from __LINE__
#define _CB_ASSERT_CT_1(a,b) _CB_ASSERT_CT_2(a,b)

//generates an error
#define _CB_ASSERT_CT_2(term,line) CoaAssertCompileCheck<(term)>                   \
                             compile_time_assertion_failed_in_line_##line        \
                             _COA_ATTRIBUTE_UNUSED





#endif //__CoaAssert_h__
