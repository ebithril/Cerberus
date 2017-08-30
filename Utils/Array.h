#pragma once

#include "Types.h"

#include "MemoryMacros.h"
#include <memory.h>

template<typename Type, typename SizeType=uint16>
class Array
{
public:
	typedef Type* iterator;
	typedef const Type* const_iterator;
	iterator begin() { return &myData[0]; }
	const_iterator begin() const { return &myData[0]; }
	iterator end() { return &myData[myNumberOfElemments]; }
	const_iterator end() const { return &myData[myNumberOfElemments]; }

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

	~Array()
	{
		delete[] myData;
	}

	Type& operator[](SizeType Index)
	{
		return myData[Index];
	}

	const Type& operator[](SizeType Index) const
	{
		return myData[Index];
	}

	SizeType Num() const
	{
		return myNumberOfElemments;
	}

	void Add(const Type& NewItem)
	{
		if (myNumberOfElemments >= myMax)
		{
			Grow();
		}

		myData[myNumberOfElemments++] = NewItem;
	}

	void Resize(const SizeType NewSize)
	{
		Type* OldData = myData;
		myData = new Type[NewSize];

		if (OldData && myNumberOfElemments)
		{
			memcpy(myData, OldData, sizeof(Type) * myNumberOfElemments);
		}
		myMax = NewSize;

		delete[] OldData;
	}

	void InitEmpty(const SizeType NewSize)
	{
		Resize(NewSize);
		myNumberOfElemments = NewSize;
	}

	Type* Data() const
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
