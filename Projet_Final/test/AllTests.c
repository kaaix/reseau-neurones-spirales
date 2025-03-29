#include "CuTest.h"
#include <stdlib.h>

extern void TestNeuralNet_AddTests(CuSuite*);

CuSuite* AllTests(void) {
    CuSuite* suite = CuSuiteNew();
    TestNeuralNet_AddTests(suite);
    return suite;
}