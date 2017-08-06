#include "String.h"

#include <cstring>

String::String(const int8* aString)
{
	*this = aString;
}

String::String(const String& aString)
	: String(aString.CString())
{
}

String::String(String&& aString)
	: myLength(aString.myLength)
	, myString(aString.myString)
{
	aString.myString = nullptr;
}

String::~String()
{
	delete[] myString;
}

const String& String::operator=(const int8* aString)
{
	const uint16 i = CountCString(aString);
	delete[] myString;
	Alloc(i);
	myLength = i;	

	memcpy(myString, aString, myLength);
	return *this;
}

const String& String::operator=(const String& aString)
{
	return *this = aString.CString();
}

void String::operator+=(const String& aString)
{
	Alloc((myLength + aString.myLength) - 1);
	memcpy(myString + myLength, aString.myString, aString.myLength);
}

void String::operator+=(const int8* aString)
{
	const int8* oldString = myString;
	const uint16 i = CountCString(aString);
	Alloc((myLength + i) - 1);
	memcpy(myString, oldString, myLength);
	memcpy(myString + myLength, aString, i + 1);
	delete[] oldString;
}

void String::Alloc(uint16 aLength)
{
	myString = new int8[aLength];
}

uint16 String::CountCString(const int8* aString) const
{
	uint16 i = 0;
	while (aString[i+1] != '\0')
	{
		i++;
	}
	i = i + 1;
	return i;
}

