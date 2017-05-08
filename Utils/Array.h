#pragma once

#include "Types.h"

#include <memory.h>

template<typename Type, typename SizeType=uint16>
class Array
{
public:
	typedef Type* iterator;
	typedef const Type* const_iterator;
	iterator begin() { return &myData[0]; }
	const_iterator begin() const { return &myData[0]; }
	iterator end() { return &myData[myCurNrOfItems]; }
	const_iterator end() const { return &myData[myCurNrOfItems]; }

	Array()
		: myMax(0)
		, myNumberOfElemments(0)
		, myData(nullptr)
	{
	}

	Array(SizeType InitSize)
		: Array()
	{
		Resize(InitSize);	
	}

	void Add(const Type& NewItem)
	{
		myNumberOfElemments++;
		if (myNumberOfElemments >= myMax)
		{
			Grow();
		}

		myData[myNumberOfElemments] = NewItem;
	}

	void Resize(const SizeType NewSize)
	{
		Type* OldData = myData;
		myData = new Type[NewSize];

		memcpy(myData, OldData, sizeof(Type) * myNumberOfElemments),
		myMax = NewSize;

		delete[] OldData;
	}

	Type* Data()
	{
		return myData;
	}

private:
	void Grow()
	{
		if (myMax <= 0)
		{
			Resize(1);
			return;
		}

		Resize(myMax*2);
	}

	SizeType myMax;
	SizeType myNumberOfElemments;
	Type* myData;
};