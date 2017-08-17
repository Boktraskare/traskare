# Makefile for boktraskare

CFLAGS := -std=c99 -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -Wno-switch -DDEBUG_MODE -g

SOURCES := $(wildcard *.c)
OBJECTS := $(addprefix build/, $(notdir $(SOURCES:.c=.o)))

build/boktraskare: $(SOURCES)
	@ mkdir -p build/
	@ gcc $(CFLAGS) $(SOURCES) -o $@

run:
	@ build/boktraskare

clean:
	rm -rf build

cnr: clean build/boktraskare run

.PHONY: default
