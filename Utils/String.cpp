#include "String.h"

#include <memory.h>

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
	uint16 i = 0;
	while(aString[i+1] != '\0')
	{
		i++;
	}
	i = i + 1;
	Alloc(i);
	myLength = i;	

	memcpy(myString, aString, myLength);
	return *this;
}

const String& String::operator=(const String& aString)
{
	return *this = aString.CString();
}

void String::Alloc(uint16 aLength)
{
	delete[] myString;
	myString = new int8[aLength];
}

