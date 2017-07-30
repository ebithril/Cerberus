#include "String.h"

#include <memory.h>

String::String(const int8* aString)
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
}

String::String(const String& aString)
	: String(aString.CString())
{
}

void String::Alloc(uint16 aLength)
{
	myString = new int8[aLength];
}
