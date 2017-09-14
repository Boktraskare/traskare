/* ----------------------------------------------------------

   Traskare ENTRY POINT

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
#include "eval.h"

#define MAX_LINE_LENGTH 1024

static int run(const char* source) {
  initScanner(source);
  initParser();
  Ast ast = parse();

  /*
  ** Check if the parser completed without errors, if it didn't
  ** we report the errors to the user.
  */

  #ifdef DEBUG_MODE
  printAst(ast.root);
  printf("\n");
  #endif

  if (ast.error) {
    reportErrors(ast.root);
    return 1;
  } else {
    printf("Result: %llu\n", eval(ast.root));
    return 0;
  }

  // Make sure this works. Check for memory leaks with valgrind.
  freeAst(ast.root);
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
    printf("Welcome to boktraskare. cmd + d to exit.\n\n");
    repl();
  } else if (argc == 2) {
    runFile(argv[2]);
  } else {
    fprintf(stderr, "Usage: traskare [path]\n");
  }
}
