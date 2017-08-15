/* ----------------------------------------------------------

   SCANNER

   The only interface to the scanner is simply the scanToken()
   function. This means that the lexer analyses the source for 
   tokens "on demand". No list of tokens is ever buffered. This 
   detail is completely transparent to the parser. This saves
   us from having to buffer a list of tokens between the scanner
   and the parser.

   To understand everything that goes on in the scanner you
   should have a look at the token implementation.

   ---------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "scanner.h"
#include "token.h"

static bool end();
static void whitespace();
static char peekNext();
static Token number();
static bool isAtEnd();
static char peek();
static bool isDigit(char c);
static char advance();
static Token makeToken(Syncat);
static bool eof();

typedef struct {
  const char* source;
  const char* lexeme;
  const char* current;
  int line;
  int col;
} Scanner;

static Scanner scanner;

void initScanner(const char* source) {
  scanner.source  = source;
  scanner.lexeme  = source;
  scanner.current = source;
  scanner.line    = 1;
  scanner.col     = 0;
}

Token scanToken() {
  whitespace();
  scanner.lexeme = scanner.current;
  if (eof()) return makeToken(SC_EOF);

  char c = advance();
  switch (c) {
    case '+': return makeToken(SC_ADD); break;
    case '-': return makeToken(SC_SUB); break;
    case '*': return makeToken(SC_MUL); break;
    case '/': return makeToken(SC_DIV); break;
    case '(': return makeToken(SC_LPR); break;
    case ')': return makeToken(SC_RPR); break;
    default:
      if(isDigit(c)) {
        return number();
      }
  }

  /*
  ** If the scanner comes across a character it doesn't know
  ** what to do with it emits a token with the syntactic
  ** category of "unknown" and leaves it to the caller to
  ** decide whatever that means.
  */

  return makeToken(SC_UKN);
}

static Token makeToken(Syncat syncat) {
  Token token;
  token.syncat = syncat;
  token.lexeme.start = scanner.lexeme;
  token.lexeme.length = (int) (scanner.current - scanner.lexeme);
  token.lineNumber = scanner.line;
  token.col = scanner.col;
  return token;
}

static void whitespace() {
  while (true) {
    switch(peek()) {
      case ' ':
      case '\r':
      case '\t':
        advance();
        break;
      case '\n':
        scanner.line++;
        scanner.col = 0;
        advance();
        break;
      default:
        return;
    }
  }
}

static bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

static char advance() {
  scanner.current++;
  scanner.col++;
  return scanner.current[-1];
}

static char peek() {
  return *scanner.current;
}

static Token number() {
  while (isDigit(peek())) advance();
  return makeToken(SC_NUM);
}

static bool eof() {
  return *scanner.current == '\0';
}
