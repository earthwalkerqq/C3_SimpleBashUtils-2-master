CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: build

s21_cat:

s21_grep:

build: s21_cat s21_grep

style-check:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i ./cat/*.c ./cat/*.h ./grep/*.c ./grep/*.h
	rm -rf ./.clang-format

clean:
	rm -rf ./a.out
	rm -rf ./*.o
	rm -rf ./cat/s21_cat
	rm -rf ./grep/s21_grep

rebuild: clean build