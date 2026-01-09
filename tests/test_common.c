#include "common.h"
#include "unity.h"
#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

// --- Tests for is_number() ---

void test_is_number_should_return_true_for_valid_number(void)
{
	TEST_ASSERT_TRUE(is_number("12345"));
}

void test_is_number_should_return_false_for_letters(void)
{
	TEST_ASSERT_FALSE(is_number("abc"));
}

void test_is_number_should_return_false_for_mixed_content(void)
{
	TEST_ASSERT_FALSE(is_number("123abc"));
}

// --- Tests for state_to_string() ---

void test_state_to_string_should_return_established(void)
{
	TEST_ASSERT_EQUAL_STRING("TCP_ESTABLISHED", state_to_string(0x01));
}

void test_state_to_string_should_return_listen(void)
{
	TEST_ASSERT_EQUAL_STRING("TCP_LISTEN", state_to_string(0x0A));
}

void test_state_to_string_should_return_time_wait(void)
{
	TEST_ASSERT_EQUAL_STRING("TCP_TIME_WAIT", state_to_string(0x06));
}

void test_state_to_string_should_return_close_wait(void)
{
	TEST_ASSERT_EQUAL_STRING("CLOSE_WAIT", state_to_string(0x08));
}

void test_state_to_string_should_return_other_for_unknown_state(void)
{
	TEST_ASSERT_EQUAL_STRING("OTHER", state_to_string(0xFF));
}

// --- Tests for addr_to_string() ---

void test_addr_to_string_should_format_localhost(void)
{
	char buffer[32];
	addr_to_string(0x7F000001, 8080, buffer, sizeof(buffer));
	TEST_ASSERT_EQUAL_STRING("127.0.0.1:8080", buffer);
}

void test_addr_to_string_should_format_zero_address(void)
{
	char buffer[32];
	addr_to_string(0x00000000, 80, buffer, sizeof(buffer));
	TEST_ASSERT_EQUAL_STRING("0.0.0.0:80", buffer);
}

void test_addr_to_string_should_handle_different_ports(void)
{
	char buffer[32];
	addr_to_string(0x7F000001, 443, buffer, sizeof(buffer));
	TEST_ASSERT_EQUAL_STRING("127.0.0.1:443", buffer);
}

// --- Test runner ---

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_is_number_should_return_true_for_valid_number);
	RUN_TEST(test_is_number_should_return_false_for_letters);
	RUN_TEST(test_is_number_should_return_false_for_mixed_content);

	RUN_TEST(test_state_to_string_should_return_established);
	RUN_TEST(test_state_to_string_should_return_listen);
	RUN_TEST(test_state_to_string_should_return_time_wait);
	RUN_TEST(test_state_to_string_should_return_close_wait);
	RUN_TEST(test_state_to_string_should_return_other_for_unknown_state);

	RUN_TEST(test_addr_to_string_should_format_localhost);
	RUN_TEST(test_addr_to_string_should_format_zero_address);
	RUN_TEST(test_addr_to_string_should_handle_different_ports);

	return UNITY_END();
}
