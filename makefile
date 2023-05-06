BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
TARGET_EXEC ?= main

SDL_LIBS := #-pthread

ifeq ($(OS),Windows_NT)
	detected_os := win
	detected_out := exe
	PREFIX := /c/msys64/mingw64
	LIBS := -lws2_32 -lwsock32 -lm $(SDL_LIBS)
else
	detected_out := out
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		detected_os := linux
		LIBS := -lm $(SDL_LIBS)
	endif
	ifeq ($(UNAME_S),Darwin)
		detected_os := mac
		PREFIX := /opt/homebrew
		LIBS := -lm $(SDL_LIBS)
	endif
endif

ifeq ($(detected_os),win)
	INCS := -I$(PREFIX)/include
	LIBS := -L$(PREFIX)/lib $(LIBS)
else ifeq ($(detected_os),mac)
	INCS := -I$(PREFIX)/include
	LIBS := -L$(PREFIX)/lib $(LIBS)
endif

TARGET_EXEC := $(TARGET_EXEC).$(detected_out)

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

WARN ?= -pedantic -W -Wall -Werror -Wshadow -Wdouble-promotion -fno-common -Wundef -Wno-unused-parameter
CPPFLAGS ?= $(WARN) $(INC_FLAGS) $(INCS) -MMD -MP

ifeq ($(detected_os),mac)
	SANITIZE_FLAG := -fsanitize=address
else
	SANITIZE_FLAG :=
endif

.PHONY: all
all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(UDP_PROTOCOL_LIB)
	$(CC) $(SANITIZE_FLAG) $(OBJS) -o $@ $(LIBS) $(UDP_PROTOCOL_LIB)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(SANITIZE_FLAG) $(CPPFLAGS) -g -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: dev
dev:
	make -s && ./build/$(TARGET_EXEC)

.PHONY: debug
debug:
	make -s && lldb ./build/$(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p

$(UDP_PROTOCOL_LIB):
	$(MAKE) -C $(UDP_PROTOCOL_DIR)
