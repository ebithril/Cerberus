#include "FileOperations.h"

#include <stdio.h>
#include "UString.h"

void ReadFileIntoArray(const String& FileName, Array<int8>& outArray)
{
	FILE* file = fopen(FileName.CString(), "r");

	fseek(file, 0L, SEEK_END);
	int32 fileSize = ftell(file);
	fseek(file, 0L, SEEK_SET);

	outArray.InitEmpty(fileSize);
	fread((void*)outArray.Data(), sizeof(int8), fileSize, file);

	fclose(file);
}
