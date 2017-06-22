#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024

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

        //result = run(line);
        printf("%s\n", line);
    }
}

// The entrypoint of the interpreter.
static void run(const char* source) {
    // Not yet implemented, just print the source for now.
    printf("%s", source);
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
