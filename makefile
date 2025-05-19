CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -g

SRC_DIR = src
BIN_DIR = bin
INC_DIR = include

COMMON_SRCS = $(SRC_DIR)/Card.cpp $(SRC_DIR)/Wallet.cpp $(SRC_DIR)/TransactionLogger.cpp
WM_SRCS = $(SRC_DIR)/wallet_manager.cpp $(COMMON_SRCS)
RW_SRCS = $(SRC_DIR)/remote_wallet.cpp $(COMMON_SRCS)

WM_TARGET = $(BIN_DIR)/wallet_manager.exe
RW_TARGET = $(BIN_DIR)/remote_wallet.exe

all: $(WM_TARGET) $(RW_TARGET)

$(WM_TARGET): $(WM_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(RW_TARGET): $(RW_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(BIN_DIR)/*.exe
