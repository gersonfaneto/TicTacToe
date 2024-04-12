# Compiler to be used.
CC = gcc

# Name for the main executable of the project.
TARGET_NAME = game

# Directories related to the build project.
BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Location for the main executable of the project.
TARGET = $(BUILD_DIR)/bin/$(TARGET_NAME)

# Files to be included in the compilation.
SOURCES_WITH_HEADERS = \
											 src/app/mouse.c \
											 src/app/window.c \
											 src/common/termctl.c \
											 src/common/algorithm.c \

# Directories to be included in the compilation.
INCLUDE_DIRS = \
							 ./src \

# Entry point for the project.
MAIN_FILE = src/main.c

# All *.c files.
SOURCES = \
					$(MAIN_FILE) \
					$(SOURCES_WITH_HEADERS)

# All *.h files.
HEADERS = \
					$(SOURCES_WITH_HEADERS:.c=.h) \
					src/config.h \
					src/utils/ui.h \
					src/common/types.h \

# Files (*.c or *.h) to be ignored in the `format` target.
IGNORE_FILES_FORMAT =

# Files (*.c or *.h) to be included in the `format` target.
HEADERS_FORMAT = $(filter-out $(IGNORE_FILES_FORMAT), $(HEADERS))
SOURCES_FORMAT = $(filter-out $(IGNORE_FILES_FORMAT), $(SOURCES))

# Names for the Object files generated from the compilation.
OBJECT_NAMES = $(SOURCES:.c=.o)

# Paths to the Object files generated from the compilation.
OBJECTS = $(patsubst %, $(OBJ_DIR)/%, $(OBJECT_NAMES))

# Flags to tune error levels in the compilation process.
WFLAGS = -Wall -Wextra -Werror -pedantic
WFLAGS += -Wno-unused-parameter  -Wno-unused-variable -Wno-unused-but-set-variable

# Flags to be passed in the compilation and linking process, respectively.
CFLAGS = -std=c99
CFLAGS += $(WFLAGS) $(addprefix -I, $(INCLUDE_DIRS))
LDFLAGS = $(addprefix -I, $(INCLUDE_DIRS))

help: ## Show all the available targets.
	@echo "Available targets:"
	@grep -E "^[a-zA-Z0-9_-]+:.*?## .*$$" $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

all: build run ## Executes the `build` and `run` targets, in that order.

# Linking...
$(TARGET): $(OBJECTS) $(HEADERS)
	@echo $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

# Compilation...
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

build: $(TARGET) ## Compiles the project.

run: $(TARGET) ## Runs the project.
	@./$^

format: ## Formats code using `clang-format`.
ifeq (, $(shell which clang-format 2> /dev/null))
	$(error `clang-format` wasn't found! Consider installing it trough your package manager)
else
	@clang-format -i $(SOURCES_FORMAT) $(HEADERS_FORMAT)
endif

clean: ## Remove all files generated in the compilation.
	@rm -rf $(BUILD_DIR)

.PHONY: all help format build run clean
