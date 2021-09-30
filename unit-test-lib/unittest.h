/*
 * unit test lib
 * the syntax mimic Microsoft Unit Testing Framework
 *   so that migrating tests from it is easier:
 * 
 *   Assert::foo() becomes Assert_foo()
 */

#include <cstdio>
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

int verbose = 0;
int n_classes = 0;
int n_methods = 0;
int n_failures = 0;
int n_asserts = 0;
void print_stats()
{
  puts("\n\n\n");
  puts("============END OF TEST============");
  printf("TESTED: %d class(es), %d method(s)\n", n_classes, n_methods);
  printf("ASSERTIONS: %d total, %d failed, %d passed\n", 
      n_asserts, n_failures, n_asserts - n_failures);
}

#define TEST_CLASS(c) {++n_classes;printf("\n\n\n~~~TEST_CLASS %s~~~\n", #c);}

#define TEST_METHOD(m) {++n_methods;printf("\n----\nTEST_METHOD %s\n", #m);}

#define Assert_AreEqual(a, b) \
{\
  ++n_asserts;\
  if (verbose) puts("testing ("#a") == ("#b")");\
  auto a_result = (a);\
  auto b_result = (b);\
  if (!(a_result == b_result)) {\
    ++n_failures;\
    if (!verbose) puts("testing ("#a") == ("#b")");\
    cerr << "LHS:\t" << a_result << endl;\
    cerr << "RHS:\t" << b_result << endl;\
    puts("\tFAILURE");\
  }\
  else if (verbose) puts("\tpass");\
}

#define Assert_AreNotEqual(a, b)\
{\
  ++n_asserts;\
  if (verbose) puts("testing ("#a") != ("#b")");\
  auto a_result = (a);\
  auto b_result = (b);\
  if (!((a_result) != (b_result))) {\
    ++n_failures;\
    if (!verbose) puts("testing ("#a") != ("#b")");\
    cerr << "LHS:\t" << a_result << endl;\
    cerr << "RHS:\t" << b_result << endl;\
    puts("\tFAILURE");\
  }\
  else if (verbose) puts("\tpass");\
}

#define Assert_IsTrue(a)\
{\
  ++n_asserts;\
  if (verbose) puts("testing ("#a") == true");\
  auto a_result = (a);\
  if (!(a_result)) {\
    ++n_failures;\
    if (!verbose) puts("testing ("#a") == true");\
    cerr << "LHS:\t" << a_result << endl;\
    puts("\tFAILURE");\
  }\
  else if (verbose) puts("\tpass");\
}

#define Assert_IsFalse(a)\
{\
  ++n_asserts;\
  if (verbose) puts("testing ("#a") == true");\
  auto a_result = (a);\
  if ((a_result)) {\
    if (!verbose) puts("testing ("#a") == true");\
    ++n_failures;\
    cerr << "LHS:\t" << a_result << endl;\
    puts("\tFAILURE");\
  }\
  else if (verbose) puts("\tpass");\
}

template<typename Exc>
void Assert_ExpectException(const std::function<void()>& thunk)
{
  ++n_asserts;
  if (verbose) puts("testing a function that must throw exception");
  bool caught = false;
  try {
    thunk();
  } catch(Exc& e) {
    caught = true;
  }
  if (!caught) {
    ++n_failures;
    if (!verbose) puts("testing a function that must throw exception");
    puts("\tFAILURE");
  }
  else if (verbose) puts("\tpass");
}
