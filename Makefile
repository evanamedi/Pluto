CC = gcc
CFLAGS = -Wall -Wextra -g

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP_FILES = $(OBJ_FILES:.o=.d)

EXEC = custom_shell

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -MMD -MP -c -o $@ $<

-include $(DEP_FILES)

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean