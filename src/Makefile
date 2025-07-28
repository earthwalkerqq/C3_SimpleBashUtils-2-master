CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: build

s21_cat: ./cat/s21_cat.c
	$(CC) $(CFLAGS) ./cat/s21_cat.c ./cat/output_file.c -o ./cat/s21_cat

s21_grep: ./grep/s21_grep.c
	$(CC) $(CFLAGS) ./grep/s21_grep.c ./grep/grep_with_flag.c -o ./grep/s21_grep

build: s21_cat s21_grep

style_check:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i cat/*.c cat/*.h
	clang-format -i grep/*.c grep/*.h
	rm -rf ./.clang-format

clean:
	rm -rf ./a.out
	rm -rf ./*.o
	rm -rf ./cat/a.out
	rm -rf ./grep/a.out
	rm -rf ./cat/s21_cat
	rm -rf ./grep/s21_grep

rebuild: clean build