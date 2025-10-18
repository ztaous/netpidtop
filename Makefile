# flags and compiler
CC = gcc
CFLAGS = -Wall -Wextra -g

# directories
SRC_DIR = src
BUILD_DIR = build

# target
TARGET = netpidtop

# source files
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/process.c
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/process.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean all