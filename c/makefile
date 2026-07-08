CC = gcc
CFLAGS := -Wall -Wextra -Iinclude -Ithird-party
LDFLAGS := ./third-party/curl-8.21.0/build/lib/libcurl.so
SRCS := $(wildcard src/*.c)
BUILD_DIR := build

OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:%.c=$(BUILD_DIR)/%.o)

# legacysdk-installer: CFLAGS += -g
installer: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) installer libcurl.so libzip.so

