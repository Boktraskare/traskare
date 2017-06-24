#ifndef scanner_h
#define scanner_h

#include "token.h"

void initScanner(const char* source);
Token scanToken();

#endif
