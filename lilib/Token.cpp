#include "Token.h"

liToken::liToken(liString lexeme, liString file, uint32_t line, uint16_t flags)
{
	this->lexeme = lexeme;
	this->file = file;
	this->line = line;
	this->flags = flags;
}