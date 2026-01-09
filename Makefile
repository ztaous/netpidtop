# flags and compiler
CC ?= gcc
CFLAGS = -Wall -Wextra -g

# flags for libraries
LIBS = -lncurses

# directories
SRC_DIR = src
BUILD_DIR = build

# target
TARGET = netpidtop

# source files
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/process.c $(SRC_DIR)/network.c $(SRC_DIR)/common.c $(SRC_DIR)/ui.c
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/process.o $(BUILD_DIR)/network.o $(BUILD_DIR)/common.o $(BUILD_DIR)/ui.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TARGET)
	rm -rf $(TEST_BINARIES)

.PHONY: clean all

# ---------

# Unity tests
UNITY_DIR = third_party/unity
TEST_DIR = tests

# source files needed for testing
SRC_MODULES = \
	$(SRC_DIR)/process.c \
	$(SRC_DIR)/network.c \
	$(SRC_DIR)/common.c

# test binaries
TEST_BINARIES = \
	$(TEST_DIR)/test_common

# to test future libraries if needed
TEST_LIBS =

.PHONY: test sanitize format-check

# build the test binaries
$(TEST_DIR)/test_common: $(TEST_DIR)/test_common.c $(SRC_MODULES) $(UNITY_DIR)/unity.c
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(UNITY_DIR) $^ -o $@ $(TEST_LIBS)

# run tests
test: $(TEST_BINARIES)
	@$(TEST_DIR)/run_tests.sh

# sanitizer build
sanitize: CFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
sanitize: LDFLAGS += -fsanitize=address,undefined
sanitize:
	$(MAKE) clean
	$(MAKE) test CC=clang

# clang-format
format-check:
	clang-format --dry-run --Werror $$(find $(SRC_DIR) $(TEST_DIR) -name "*.c" -o -name "*.h")

format:
	clang-format -i $$(find $(SRC_DIR) $(TEST_DIR) -name "*.c" -o -name "*.h")