# Compiler
CC := gcc

# Directories
SRC_DIR := source
INC_DIR := include
DOT_DIR := $(SRC_DIR)/dot

# Files
SRCS := $(wildcard $(SRC_DIR)/*.c) main.c
OBJS := $(patsubst $(SRC_DIR)/%.c,%.o,$(filter-out main.c,$(SRCS)))
MAIN_OBJ := main.o
DEPS := $(wildcard $(INC_DIR)/*.h)

# Compiler flags
CFLAGS := -std=c11 -Wall -Wextra -g

# Output executable
TARGET := grafo

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(MAIN_OBJ): main.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
# @rm -f $(OBJS) $(MAIN_OBJ) $(TARGET) - incompatível com o Windows.  Trocado pelo cmd del, que é específico para o Windows
	@del /Q $(OBJS) $(MAIN_OBJ) $(TARGET)
	@for %%f in ($(DOT_DIR)\*.dot) do del "%%f"
