# Colors
GREEN := \033[0;32m
BLUE  := \033[0;34m
RED   := \033[0;31m
RESET := \033[0m

# Flags
CXX       = g++
CXXFLAGS  = -Wall -Wextra -pedantic -MMD -MP
LDFLAGS   =

# Build Type
BUILD_TYPE ?= Debug

ifeq ($(BUILD_TYPE), Debug)
  CXXFLAGS += -O0 -g
else ifeq ($(BUILD_TYPE), Release)
  CXXFLAGS += -O2
endif

#Folders
SRC_DIR    = src
MODULE_DIR = module
BUILD_DIR  = build
TARGET     = my_program

# 4. Includes
INC_DIRS  = $(shell find $(MODULE_DIR) -type d)
INC_DIRS += $(SRC_DIR)
INC_FLAGS    = $(patsubst %, -I%, $(INC_DIRS))


MAIN_SOURCES = $(wildcard $(SRC_DIR)/*.c++) \
               $(wildcard $(MODULE_DIR)/*/*.c++)
MAIN_OBJECTS = $(patsubst %.c++,$(BUILD_DIR)/%.o,$(MAIN_SOURCES))
MAIN_DEPS    = $(MAIN_OBJECTS:.o=.d)

.PHONY: all clean rebuild build success

all: success

# If everything builds, we print a final success message:
success: $(TARGET)
	@echo "$(GREEN)Build successful!$(RESET)"

rebuild: clean all

clean:
	@echo "$(RED)Cleaning build directory$(RESET)"
	@rm -rf $(BUILD_DIR) $(TARGET)

# Parallel build convenience target
build:
	@echo "$(BLUE)Running parallel build...$(RESET)"
	@$(MAKE) -j$(shell nproc) all

$(TARGET): $(MAIN_OBJECTS)
	@echo "Linking $(TARGET) ..."
	@$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c++
	@mkdir -p $(dir $@)
	@if [ -f $@ ]; then \
		echo "$(BLUE)Recompiling $(RESET)$<"; \
	else \
		echo "$(GREEN)Compiling   $(RESET)$<"; \
	fi
	@$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

-include $(MAIN_DEPS)
