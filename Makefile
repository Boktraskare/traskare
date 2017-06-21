# Makefile for boktraskare

CFLAGS := -std=c99 -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter

default:
	@ mkdir -p build
	@ gcc $(CFLAGS) main.c -o build/main.o

run:
	@ build/main.o

clean:
	rm -rf build
