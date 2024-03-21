#include "Lexer.h"

liLexer::liLexer(liString source, liList<liString> keywords, liList<liString> datatypes)
{
	this->source = source;
	this->keywords = keywords;
	this->datatypes = datatypes;
}

liLexer::~liLexer()
{
}

void liLexer::Analyze()
{
}

void liLexer::ResetMetrics()
{
	this->errors = 0;
	this->warnings = 0;
}

bool liLexer::IsKeyword(liString str) const
{
	for (int i = 0; i < keywords.Size(); i++) {
		if (str == keywords[i])
			return true;
	}
	return false;
}

bool liLexer::IsDatatype(liString str) const
{
	for (int i = 0; i < datatypes.Size(); i++) {
		if (str == datatypes[i])
			return true;
	}
	return false;
}