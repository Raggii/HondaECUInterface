# Colors
GREEN := \033[0;32m
BLUE  := \033[0;34m
RED   := \033[0;31m
RESET := \033[0m

# Compilers & Flags
# Use C compiler for .c (LVGL)
CC       = gcc
CXX      = g++

CFLAGS   = -Wall -Wextra -pedantic -std=c99 -MMD -MP
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -MMD -MP
LDFLAGS  =

BUILD_TYPE ?= Debug

ifeq ($(BUILD_TYPE), Debug)
  CFLAGS   += -O0 -g
  CXXFLAGS += -O0 -g
else ifeq ($(BUILD_TYPE), Release)
  CFLAGS   += -O2
  CXXFLAGS += -O2
endif

# Folders
SRC_DIR    = src
MODULE_DIR = module
BUILD_DIR  = build
TARGET     = executable

# Includes
INC_DIRS  = $(shell find $(MODULE_DIR) -type d)
INC_DIRS += $(SRC_DIR)
INC_FLAGS = $(patsubst %, -I%, $(INC_DIRS))

# LVGL Integration
LVGL_DIR       = libs/lvgl
LVGL_SRC_DIR   = $(LVGL_DIR)/src
LVGL_C_SOURCES = $(shell find $(LVGL_SRC_DIR) -type f -name "*.c")
LVGL_OBJ_DIR   = $(BUILD_DIR)/lvgl
LVGL_OBJECTS   = $(patsubst $(LVGL_SRC_DIR)/%.c, $(LVGL_OBJ_DIR)/%.o, $(LVGL_C_SOURCES))

# Static library filename
LVGL_STATIC_LIB = $(LVGL_OBJ_DIR)/liblvgl.a
INC_FLAGS += -I$(LVGL_DIR) -I$(LVGL_SRC_DIR)

# SDL2 Integration
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

# Append SDL2 flags to CXXFLAGS and LDFLAGS
CXXFLAGS += $(SDL_CFLAGS)
LDFLAGS  += $(SDL_LDFLAGS)

MAIN_SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
               $(wildcard $(MODULE_DIR)/*/*.cpp)

MAIN_OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(MAIN_SOURCES))
MAIN_DEPS    = $(MAIN_OBJECTS:.o=.d)

# Phony Targets
.PHONY: all clean rebuild build success

all: success

success: $(TARGET)
	@echo "$(GREEN)Build successful!$(RESET)"

rebuild: clean all

clean:
	@echo "$(RED)Cleaning build directory$(RESET)"
	@rm -rf $(BUILD_DIR) $(TARGET)

build:
	@echo "$(BLUE)Running parallel build...$(RESET)"
	@$(MAKE) -j$(shell nproc) all

$(TARGET): $(MAIN_OBJECTS) $(LVGL_STATIC_LIB)
	@echo "Linking $(TARGET) ..."
	# Link with g++ and SDL2
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# LVGL: Build as a C static library
$(LVGL_STATIC_LIB): $(LVGL_OBJECTS)
	@echo "Archiving LVGL into static library $@"
	@ar rcs $@ $^

# Compiling LVGL C Sources
$(LVGL_OBJ_DIR)/%.o: $(LVGL_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@if [ -f $@ ]; then \
		echo "$(BLUE)Recompiling $(RESET)$<"; \
	else \
		echo "$(GREEN)Compiling   $(RESET)$<"; \
	fi
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Compiling Main C++ Sources
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@if [ -f $@ ]; then \
		echo "$(BLUE)Recompiling $(RESET)$<"; \
	else \
		echo "$(GREEN)Compiling   $(RESET)$<"; \
	fi
	@$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

# Auto-Dependency Includes
-include $(MAIN_DEPS)
