#include "FileOperations.h"

#include <stdio.h>
#include "UString.h"

typedef FILE FileHandle;

FileHandle* OpenFile(const String& FileName, const String& Mode)
{
	return fopen(FileName.CString(), Mode.CString());
}

void CloseFile(FileHandle* Handle)
{
	fclose(Handle);
}

int32 GetFileSize(FileHandle* Handle)
{
	fseek(Handle, 0L, SEEK_END);
	const int32 fileSize = ftell(Handle);
	fseek(Handle, 0L, SEEK_SET);
	return fileSize;
}

void ReadFromFile(void* dst, int32 size, int32 count, FileHandle* Handle)
{
	fread(dst, size, count, Handle);	
}

void ReadFileIntoArray(const String& FileName, Array<int8>& outArray)
{
	FileHandle* file = OpenFile(FileName, "r");

	const int32 fileSize = GetFileSize(file);

	outArray.InitEmpty(fileSize);
	ReadFromFile((void*)outArray.Data(), sizeof(int8), fileSize, file);

	CloseFile(file);
}

