# Makefile for boktraskare

CFLAGS := -std=c99 -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter

SOURCES := $(wildcard *.c)
OBJECTS := $(addprefix build/, $(notdir $(SOURCES:.c=.o)))

build/boktraskare: $(SOURCES)
	@ mkdir -p build/
	@ gcc $(CFLAGS) $(SOURCES) -o $@

run:
	@ build/boktraskare

clean:
	rm -rf build

.PHONY: default
