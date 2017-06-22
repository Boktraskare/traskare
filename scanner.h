#ifndef scanner_h
#define scanner_h

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
} TokenType;

typedef struct {
    TokenType   type;
    const char* start;
    int         length;
    int         line;
} Token;

void initScanner(const char* source);

Token scanToken();

#endif
