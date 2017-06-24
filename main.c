#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "scanner.h"

#define MAX_LINE_LENGTH 1024

// The entrypoint of the interpreter.
static void run(const char* source) {
    initScanner(source);

    while (true) {
        Token t = scanToken();
        printf("TOKENTYPE: %s, LEXEME: %.*s\n", ttos(t.type), t.length, t.start);

        if (t.type == TOKEN_EOF) {
            break;
        }
    }
}

// A read-eval-print loop for interactive testing of the interpreter.
static void repl() {
    char line[MAX_LINE_LENGTH];

    while (true) {
        printf("trask > "); 

        // Exit REPL if fgets unsuccessful
        if (!fgets(line, MAX_LINE_LENGTH, stdin)) {
            printf("\n"); 
            break;
        }

        // Cut last "\n"
        line[strlen(line) - 1] = '\0';

        run(line);
        printf("\n"); 
    }
}

// Read the file specified at path and feed it to run().
static void runFile(const char* path) {
    printf("%s", path);
} 

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        printf("Welcome to boktraskare. cmd + d to exit.");
        printf("\n");
        printf("\n");
        repl();
    } else if (argc == 2) {
        runFile(argv[2]);
    } else {
        fprintf(stderr, "Usage: traskare [path]\n");
    }
}
