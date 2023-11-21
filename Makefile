CC = g++
CFLAGS = -Wall -Wextra -pedantic -Wno-unused-parameter -Werror=init-self -ggdb

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

.PHONY: all
all: setup sim

.PHONY: setup
setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

sim: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

-include $(DEP_FILES)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*


