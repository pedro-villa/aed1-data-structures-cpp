CXX      := g++
CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -Wpedantic

BIN_DIR  := bin
SRC_DIR  := 01-dictionary-trie-hashtable-cpp/src
TEST_DIR := 01-dictionary-trie-hashtable-cpp/tests

TARGET   := $(BIN_DIR)/diccionario_aed1
SRCS     := $(SRC_DIR)/004final.cpp \
            $(SRC_DIR)/diccionario.cpp \
            $(SRC_DIR)/arbolTrie.cpp \
            $(SRC_DIR)/TablaHash.cpp

.PHONY: all test clean

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

test: $(TARGET)
	@bash $(TEST_DIR)/run_tests.sh

clean:
	rm -rf $(BIN_DIR) $(SRC_DIR)/*.o $(SRC_DIR)/a.out actual_output.txt
