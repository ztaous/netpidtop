#include "unity.h"
#include "process.h"
#include "network.h"
#include "common.h"

void setUp(void) {

}

void tearDown(void) {

}

void test_example_should_pass(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

void test_parse_process_line(void) {
    TEST_ASSERT_TRUE(1);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_example_should_pass);
    RUN_TEST(test_parse_process_line);
    
    return UNITY_END();
}