#pragma once

#include "Types.h"
#include "MemoryMacros.h"

class String
{
public:
	String(const int8* aString);
	String(const String& aString);
	String(String&& aString);
	~String();

	const String& operator=(const int8* aString);
	const String& operator=(const String& aString);
	void operator+=(const String& aString);
	void operator+=(const int8* aString);

	uint16 Length() { return myLength; }


	const int8* CString() const { return myString; }
private:
	void Alloc(uint16 aLength);
	uint16 CountCString(const int8* aString) const;

	uint16 myLength = 0;
	int8* myString = nullptr;
};

