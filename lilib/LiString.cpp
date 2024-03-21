#include "LiString.h"

liString::liString() : liList<char>()
{
}

liString::liString(const char* str) : liList<char>()
{
	size_t length = strlen(str);
	Resize(length + 1);
	for (size_t i = 0; i < length; i++) {
		Push(str[i]);
	}
	data[Size()] = '\0';
}

liString::liString(const char* buffer, size_t buffer_length)
{
	size_t length = buffer_length;
	Resize(length + 1);
	for (size_t i = 0; i < length; i++) {
		Push(buffer[i]);
	}
	data[Size()] = '\0';
}

liString::liString(unsigned char* buffer, size_t buffer_length) : liList<char>()
{
	size_t length = buffer_length;
	Resize(length);
	for (size_t i = 0; i < length; i++) {
		Push(buffer[i]);
	}
}

liString::liString(const liString& str) : liList<char>()
{
	this->Copy(str, 1);
	this->data[Size()] = '\0';
}

const liString& liString::operator=(const liString& right)
{
	this->Copy(right, 1);
	this->data[Size()] = '\0';
	return *this;
}

bool liString::operator==(const liString& right)
{
	return !strcmp(data, right.data);
}

void liString::Append(char c)
{
	size_t index = Size();
	Resize(index + 2);
	Push(c);
	this->data[Size()] = '\0';
}

void liString::Append(cstring str)
{
	size_t app_length = strlen(str);
	size_t length = Size();
	Resize(length + app_length + 1);
	for (size_t i = 0; i < app_length; i++) {
		Push(str[i]);
	}
	this->data[Size()] = '\0';
}

void liString::Append(liString str)
{
	Append(str.c_str());
}

liString liString::operator+(char c)
{
	liString str = *this;
	str.Append(c);
	return str;
}

liString liString::operator+(cstring str)
{
	liString output = *this;
	output.Append(str);
	return output;
}

liString liString::operator+(liString str)
{
	liString output = *this;
	output.Append(str);
	return output;
}

cstring liString::c_str() const
{
	return data;
}

size_t liString::Length() const
{
	return size;
}

bool liString::Contains(char* substr)
{
	return strstr(data, substr);
}

int liString::First(char c, int start)
{
	for (size_t i = start; i < Length(); i++) {
		if (data[i] == c)
			return i;
	}
	return -1;
}

int liString::Last(char c)
{
	for (size_t i = Length(); i > 0; i--) {
		if (data[i] == c)
			return i;
	}
	return -1;
}

liString liString::Substring(int start, int end) const
{
	liString str;
	str.Resize(end - start);
	for (int i = start; i < end; i++) {
		str.Push(data[i]);
	}
	return str;
}

liList<liString*> liString::Tokenize(char c)
{
	liList<liString*> result;
	int start = 0;
	while (start < Length()) {
		int second = First(c, start);
		liString token;
		if (second == LISTRING_NPOS) {
			second = Length();
		}
		token = Substring(start, second);
		result.Push(new liString(token));
		start = second + 1;
	}
	return result;
}

bool liString::Empty()
{
	return Length() == 0;
}

bool liString::IsWhitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

bool liString::IsAlpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool liString::IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool liString::IsAlphanumeric(char c)
{
	return IsAlpha(c) || IsDigit(c);
}

void liString::Trim()
{
	for (size_t i = 0; i < Length(); i++) {
		char c = data[i];
		if (IsWhitespace(c)) {
			Erase(Begin() + i);
		}
	}
	Push('\0');
}

void liString::ToUpper()
{
	for (size_t i = 0; i < Length(); i++) {
		this->data[i] = toupper(data[i]);
	}
}

void liString::CleanupTokenized(liList<liString*>* tokens)
{
	tokens->DeleteDataPointers();
}

liString liString::IntToString(int i)
{
	char buffer[16] = {0};
	itoa(i, buffer, 10);
	return liString(buffer);
}

liString liString::FloatToString(float v) {
	char buffer[16] = {0};
	sprintf(buffer, "%f", v);
	return liString(buffer);
}

liString liString::BoolToString(bool v)
{
	const char* buffer;
	if (v) {
		buffer = "true";
	} else {
		buffer = "false";
	}
	return liString(buffer);
}