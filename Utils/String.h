#pragma once

#include "Types.h"
#include "MemoryMacros.h"

class String
{
public:
	String(const int8* aString);
	String(const String& aString);
	uint16 Length() { return myLength; }


	const int8* CString() const { return myString; }
private:
	void Alloc(uint16 aLength);

	uint16 myLength = 0;
	int8* myString = nullptr;
};
