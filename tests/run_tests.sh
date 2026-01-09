#!/bin/bash
# run all test binaries and return results

set -e

TEST_DIR="$(dirname "$0")"
FAILED=0

echo "Running all tests..."

for test_bin in "$TEST_DIR"/test_*; do
    if [ -x "$test_bin" ] && [ -f "$test_bin" ]; then
        echo ""
        "$test_bin" || FAILED=1
    fi
done

if [ $FAILED -eq 0 ]; then
    echo ""
    echo "================================"
    echo "All test suites passed"
    echo "================================"
    exit 0
else
    echo ""
    echo "================================"
    echo "Some tests failed"
    echo "================================"
    exit 1
fi
