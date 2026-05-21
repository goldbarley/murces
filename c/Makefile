CC := gcc
CFLAGS := -Wall -g -std=gnu11 -MMD -MP
LFLAGS := -lncurses -lpthread

INC_FLAGS := -I./precursor/include -I./murces-TUI -I./bridge -I./manager

# The main application uses murces-TUI/main.c
TUI_SRCS := $(wildcard murces-TUI/*.c)
PRECURSOR_SRCS := $(wildcard precursor/src/*.c)
BRIDGE_SRCS := bridge/communciate.c bridge/cJSON.c bridge/router.c bridge/log.c
MANAGER_SRCS := manager/commands.c manager/server_properties.c manager/modfiles.c

SRCS := $(TUI_SRCS) $(PRECURSOR_SRCS) $(BRIDGE_SRCS) $(MANAGER_SRCS)

BUILD_DIR := build
OBJ_FILES := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPEND := $(OBJ_FILES:.o=.d)
TARGET := $(BUILD_DIR)/murces

.PHONY: all clean run test_bridge test_manager

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "Linking $@"
	@$(CC) $(OBJ_FILES) -o $@ $(LFLAGS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

-include $(DEPEND)

run: all
	@cd $(BUILD_DIR) && ./murces

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

# Standalone Tests
test_bridge: $(BUILD_DIR)/bridge/main.o $(BUILD_DIR)/bridge/communciate.o $(BUILD_DIR)/bridge/cJSON.o $(BUILD_DIR)/bridge/router.o $(BUILD_DIR)/bridge/log.o
	@echo "Linking test_bridge"
	@$(CC) $^ -o $(BUILD_DIR)/$@ $(LFLAGS)

test_manager: $(BUILD_DIR)/manager/main.o $(BUILD_DIR)/manager/server_properties.o $(BUILD_DIR)/manager/commands.o $(BUILD_DIR)/manager/modfiles.o
	@echo "Linking test_manager"
	@$(CC) $^ -o $(BUILD_DIR)/$@ $(LFLAGS)
