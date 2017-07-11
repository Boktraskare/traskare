/* ----------------------------------------------------------

   TRASKARE ENTRY POINT

   Overview
   
   The interpreter is made up of three phases: scanning, parsing
   and evaluation. The scanner and the parser are global objects
   (but statically declared) hence the no arguments calls to 
   initParser() and parse().

   ---------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "ast.h"
#include "printing.h"

#define MAX_LINE_LENGTH 1024

static void run(const char* source) {
    initScanner(source);
    initParser();
    printAst(parse());
    // freeAst();
}

static void repl() {
    char line[MAX_LINE_LENGTH];
    
    while (true) {
        printf("trask > ");

        if (!fgets(line, MAX_LINE_LENGTH, stdin)) {
            printf("\n"); 
            break;
        }

        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        run(line);
        printf("\n");
    }
}

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
