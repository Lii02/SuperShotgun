#ifndef LILIB_TOKEN_H
#define LILIB_TOKEN_H
#include "EngineDefs.h"
#include "LiString.h"

#define LITOKEN_KEYWORD (1 << 0)
#define LITOKEN_DATATYPE (1 << 1)
#define LITOKEN_IDENTIFIER (1 << 3)
#define LITOKEN_OPERATOR (1 << 4)
#define LITOKEN_SEPERATOR (1 << 5)
#define LITOKEN_INT_LITERAL (1 << 7)
#define LITOKEN_STRING_LITERAL (1 << 8)
#define LITOKEN_CHAR_LITERAL (1 << 9)
#define LITOKEN_FLOAT_LITERAL (1 << 10)

class liToken {
public:
	liString lexeme;
	liString file;
	uint32_t line;
	uint16_t flags;

	liToken() = default;
	liToken(liString lexeme, liString file, uint32_t line, uint16_t flags);
};

#endif