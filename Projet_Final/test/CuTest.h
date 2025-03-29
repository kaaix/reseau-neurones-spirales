#ifndef CU_TEST_H
#define CU_TEST_H

#include <setjmp.h>
#include <stdarg.h>

/* Structure représentant un test unitaire */
typedef struct CuTest CuTest;
typedef void (*TestFunction)(CuTest *);

struct CuTest {
    char* name;
    TestFunction function;
    int failed;
    char* message;
    jmp_buf jumpBuf;
};

CuTest* CuTestNew(const char* name, TestFunction function);
void CuTestRun(CuTest* tc);
void CuFail(CuTest* tc, const char* message);
void CuAssert(CuTest* tc, const char* message, int condition);
void CuAssertTrue(CuTest* tc, int condition);
void CuAssertStrEquals(CuTest* tc, const char* expected, const char* actual);

/* Suite de tests */
typedef struct {
    CuTest** list;
    int count;
    int capacity;
} CuSuite;

CuSuite* CuSuiteNew();
void CuSuiteAdd(CuSuite* suite, CuTest* test);
void CuSuiteAddSuite(CuSuite* suite, CuSuite* otherSuite);
void CuSuiteRun(CuSuite* suite);
void CuSuiteDetails(CuSuite* suite);

/* Macro utile */
#define SUITE_ADD_TEST(suite, testFunc) CuSuiteAdd(suite, CuTestNew(#testFunc, testFunc))

#endif
