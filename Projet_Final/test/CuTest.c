#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CuTest.h"

CuTest* CuTestNew(const char* name, TestFunction function) {
    CuTest* tc = (CuTest*)malloc(sizeof(CuTest));
    tc->name = strdup(name);
    tc->function = function;
    tc->failed = 0;
    tc->message = NULL;
    return tc;
}

void CuFail(CuTest* tc, const char* message) {
    tc->failed = 1;
    tc->message = strdup(message);
    longjmp(tc->jumpBuf, 1);
}

void CuAssert(CuTest* tc, const char* message, int condition) {
    if (!condition) CuFail(tc, message);
}

void CuAssertTrue(CuTest* tc, int condition) {
    CuAssert(tc, "Assertion failed", condition);
}

void CuAssertStrEquals(CuTest* tc, const char* expected, const char* actual) {
    if ((expected == NULL && actual != NULL) ||
        (expected != NULL && actual == NULL) ||
        (expected != NULL && strcmp(expected, actual) != 0)) {
        char buf[512];
        snprintf(buf, sizeof(buf), "Expected [%s] but was [%s]", expected, actual);
        CuFail(tc, buf);
    }
}

void CuTestRun(CuTest* tc) {
    if (!setjmp(tc->jumpBuf)) {
        tc->function(tc);
    }
}

CuSuite* CuSuiteNew() {
    CuSuite* suite = (CuSuite*)malloc(sizeof(CuSuite));
    suite->list = NULL;
    suite->count = 0;
    suite->capacity = 0;
    return suite;
}

void CuSuiteAdd(CuSuite* suite, CuTest* test) {
    if (suite->count >= suite->capacity) {
        suite->capacity += 10;
        suite->list = (CuTest**)realloc(suite->list, sizeof(CuTest*) * suite->capacity);
    }
    suite->list[suite->count++] = test;
}

void CuSuiteAddSuite(CuSuite* suite, CuSuite* otherSuite) {
    for (int i = 0; i < otherSuite->count; ++i) {
        CuSuiteAdd(suite, otherSuite->list[i]);
    }
}

void CuSuiteRun(CuSuite* suite) {
    for (int i = 0; i < suite->count; ++i) {
        CuTestRun(suite->list[i]);
    }
}

void CuSuiteDetails(CuSuite* suite) {
    printf("Test Summary:\n");
    for (int i = 0; i < suite->count; ++i) {
        printf(" %s: %s\n", suite->list[i]->name, suite->list[i]->failed ? "FAIL" : "OK");
        if (suite->list[i]->failed) {
            printf("   Message: %s\n", suite->list[i]->message);
        }
    }
}
