CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = game
TESTFLAGS = MANGOHUD=1 mangohud __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia __VK_LAYER_NV_optimus=NVIDIA_only

SRC = $(shell find src -name '*.cpp') $(shell find src -name '*.c')
OBJ_DIR = build
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/src/%.o)
OBJ := $(OBJ:src/glad.c=$(OBJ_DIR)/src/glad.o)


LIBS_LINUX = -lglfw    \
	     -lGL      \
	     -ldl      \
	     -lX11     \
	     -lXrandr  \
	     -lXi      \
	     -lXxf86vm \
	     -lXcursor \
	     -lenet

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS_LINUX)

$(OBJ_DIR)/src/%.o: src/%.cpp
	mkdir -p $(dir $@z)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/src/glad.o: src/glad.c
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
	rm -rf publish

test: all
	$(TESTFLAGS) gdb -q -batch -x debug.gdb --args ./$(TARGET)

.PHONY: all test clean
