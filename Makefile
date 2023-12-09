# CC = gcc
# TARGET = myprogram
# INCLUDE = -Iinc
# CFLAGS = $(INCLUDE)
# SRC = $(wildcard lib/*.c) main.c
# OBJ = $(SRC:.c=.o)

# all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CC) $(CFLAGS) -o $@ $(OBJ)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@ 

# clean:
# 	rm -f $(OBJ) $(TARGET)

CC = gcc
TARGET = myprogram
INCLUDE = -Iinc
CFLAGS = $(INCLUDE)
SRC = $(wildcard lib/*.c) main.c
BUILD_DIR = build
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

all: $(TARGET) install

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

install:
	mv $(TARGET) $(BUILD_DIR)/$(TARGET)
clean:
	rm -rf $(BUILD_DIR) $(TARGET)



