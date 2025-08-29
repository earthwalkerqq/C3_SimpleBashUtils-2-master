CC = gcc
CFLAGS = -Wall -Werror -Wextra
ARFLAGS = rcs

GREP_INCLUDE = grep/inc
GREP_INCLUDE_UTILS = grep/common

CAT_INCLUDE = cat/inc

CAT_MAIN = cat/s21_cat.c
GREP_MAIN = grep/s21_grep.c

CAT_FILES = $(wildcard cat/src/*.c)
GREP_FILES = $(wildcard grep/src/*.c grep/common/*.c)

OBJ_CAT = $(CAT_FILES:.c=.o)
OBJ_GREP = $(GREP_FILES:.c=.o)

BUILD_FOLDER = ../build

GREP_LIB = $(BUILD_GREP)/libgrep.a
CAT_LIB = $(BUILD_CAT)/libcat.a

BUILD_CAT = $(BUILD_FOLDER)/s21_cat
BUILD_GREP = $(BUILD_FOLDER)/s21_grep

.PHONY: all build clean rebuild style_check

all: build

build: $(BUILD_CAT) s21_cat $(BUILD_GREP) s21_grep

$(BUILD_CAT):
	mkdir -p $(BUILD_CAT)

$(BUILD_GREP):
	mkdir -p $(BUILD_GREP)

$(GREP_LIB): $(OBJ_GREP)
	ar $(ARFLAGS) $@ $(wildcard ../build/s21_grep/*.o)

$(CAT_LIB): $(OBJ_CAT)
	ar $(ARFLAGS) $@ $(wildcard ../build/s21_cat/*.o)

s21_cat: $(CAT_LIB)
	$(CC) $(CFLAGS) -I$(CAT_INCLUDE) $(CAT_MAIN) $(CAT_LIB) -o $(BUILD_CAT)/cat.o

# s21_cat
$(OBJ_CAT): $(OBJ_CAT:.o=.c)
	$(CC) $(CFLAGS) -I$(CAT_INCLUDE) -c $< -o $(BUILD_CAT)/$(notdir $@)

# Компиляция s21_grep с линковкой libgrep.a
s21_grep: $(GREP_LIB)
	$(CC) $(CFLAGS) -I$(GREP_INCLUDE) -I$(GREP_INCLUDE_UTILS) $(GREP_MAIN) $(GREP_LIB) -o $(BUILD_GREP)/grep.o

# s21_grep
grep/%.o: grep/%.c
	$(CC) $(CFLAGS) -I$(GREP_INCLUDE) -I$(GREP_INCLUDE_UTILS) -c $< -o $(BUILD_GREP)/$(notdir $@)

grep/common/%.o: grep/common/%.c
	$(CC) $(CFLAGS) -I$(GREP_INCLUDE) -I$(GREP_INCLUDE_UTILS) -c $< -o $(BUILD_GREP)/$(notdir $@)

style_check:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i cat/src/*.c cat/inc/*.h cat/*.c
	clang-format -i grep/src/*.c grep/inc/*.h grep/*.c
	rm -rf ./.clang-format

clean:
	rm -rf $(BUILD_FOLDER)
	rm -rf */*/*.o
	rm -rf ./.clang-format

rebuild: clean build