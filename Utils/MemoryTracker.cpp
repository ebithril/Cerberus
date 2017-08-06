#include "MemoryTracker.h"

#include <new>
#include <malloc.h>
#include <stdio.h>

MemoryTracker* MemoryTracker::ourInstance = nullptr;

void* operator new(std::size_t Bytes)
{
	void* address = malloc(Bytes);
	MemoryTracker::GetInstance()->Add(address, Bytes, EMemoryType::New);
	return address;
}

void* operator new[](std::size_t Bytes)
{
	void* address = malloc(Bytes);
	MemoryTracker::GetInstance()->Add(address, Bytes, EMemoryType::NewArray);
	return address;
}

void operator delete(void* Address) throw()
{
	MemoryTracker::GetInstance()->Remove(Address);
	free(Address);
}

void operator delete[](void* Address) throw()
{
	MemoryTracker::GetInstance()->Remove(Address);
	free(Address);
}

void MemoryTracker::Create()
{
	ourInstance = static_cast<MemoryTracker*>(malloc(sizeof(MemoryTracker)));
	ourInstance = new(ourInstance)MemoryTracker();
	ourInstance->NumberOfAllocations = 0;
}

void MemoryTracker::Destroy()
{
	for (uint16 i = 0; i < ourInstance->NumberOfAllocations; ++i)
	{
		const MemoryData& Data = ourInstance->Allocations[i];
		printf("Memory leak at Line:%d File:%s Function:%s Size:%u \n", Data.Line, Data.FileName, Data.FunctionName, Data.Bytes);
	}

	free(ourInstance);
}

void MemoryTracker::ResetCurrentAllocation()
{
	CurrentAllocation.Line = -1;
	CurrentAllocation.FileName = "";
	CurrentAllocation.FunctionName = "";
	CurrentAllocation.Type = EMemoryType::Unknown;
}

void MemoryTracker::Add(void* Address, uint32 Bytes, EMemoryType Type)
{
	if (CurrentAllocation.Line < 1)
	{
		return;
	}

	CurrentAllocation.Address = Address;
	CurrentAllocation.Bytes = Bytes;
	CurrentAllocation.Type = Type;

	if (!CurrentAllocation.FileName)
	{
		CurrentAllocation.FileName = "Unknown";
	}

	if (!CurrentAllocation.FunctionName)
	{
		CurrentAllocation.FunctionName = "Unknown";
	}

	Allocations[NumberOfAllocations++] = CurrentAllocation;
	ResetCurrentAllocation();
}

void MemoryTracker::Remove(void* Address)
{
	for (uint16 i = 0; i < NumberOfAllocations; ++i)
	{
		MemoryData& Allocation = Allocations[i];
		if (Allocation.Address == Address)
		{
			Allocations[i] = Allocations[--NumberOfAllocations];
			return;
		}
	}
}

void MemoryTracker::Allocate(int32 Line, const int8* File, const int8* Function)
{
	CurrentAllocation.Line = Line;
	CurrentAllocation.FileName = File;
	CurrentAllocation.FunctionName = Function;
}
