# flags and compiler
CC = gcc
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
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean all