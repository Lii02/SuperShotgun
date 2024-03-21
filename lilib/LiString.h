#ifndef LISTRING_H
#define LISTRING_H
#include "List.h"

#define LISTRING_NPOS -1

class liString : public liList<char> {
private:
public:
	liString();
	liString(const char* str);
	liString(const char* buffer, size_t buffer_length);
	liString(unsigned char* buffer, size_t buffer_length);
	liString(const liString& str);
	
	const liString& operator=(const liString& right);
	bool operator==(const liString& right);
	void Append(char c);
	void Append(cstring str);
	void Append(liString str);
	liString operator+(char str);
	liString operator+(cstring str);
	liString operator+(liString c);
	cstring c_str() const;
	size_t Length() const;
	bool Contains(char* substr);
	int First(char c, int start = 0);
	int Last(char c);
	liString Substring(int start, int end) const;
	liList<liString*> Tokenize(char c);
	bool Empty();
	static bool IsWhitespace(char c);
	static bool IsAlpha(char c);
	static bool IsDigit(char c);
	static bool IsAlphanumeric(char c);
	void Trim();
	void ToUpper();

	static void CleanupTokenized(liList<liString*>* tokens);
	static liString IntToString(int i);
	static liString FloatToString(float v);
	static liString BoolToString(bool v);
};

#endif