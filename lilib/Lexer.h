#ifndef LILIB_LEXER_H
#define LILIB_LEXER_H
#include "EngineDefs.h"
#include "Token.h"
#include "List.h"

class liLexer {
private:
	liString source;
	liList<liString> keywords, datatypes;
	liList<liToken> tokens;
	uint32_t errors, warnings;
public:
	liLexer(liString source, liList<liString> keywords, liList<liString> datatypes);
	~liLexer();

	void Analyze();
	void ResetMetrics();
	bool IsKeyword(liString str) const;
	bool IsDatatype(liString str) const;
};

#endif