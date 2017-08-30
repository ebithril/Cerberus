#pragma once

#include "Types.h"

#define MAX_ALLOCATIONS 65535

enum class EMemoryType : uint8
{
	New,
	NewArray,
	Unknown,
};

struct MemoryData
{
	uint32 Bytes;
	int32 Line;
	EMemoryType Type;
	const int8* FileName;
	const int8* FunctionName;
	void* Address;
};

class MemoryTracker
{
public:
	static MemoryTracker* GetInstance() { return ourInstance; }
	static void Create();
	static void Destroy();

	void Add(void* Address, uint32 Bytes, EMemoryType Type);
	void Remove(void* Address);

	void Allocate(int32 Line, const int8* File, const int8* Function);

private:
	static MemoryTracker* ourInstance;

	void ResetCurrentAllocation();

	MemoryData Allocations[MAX_ALLOCATIONS];
	uint16 NumberOfAllocations;

	MemoryData CurrentAllocation;
};