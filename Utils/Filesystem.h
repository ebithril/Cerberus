#pragma once

#include "UString.h"
#include "Array.h"

class FileSystem
{
public:
	static void InitBaseDirectory();
	static void GetAllFilesInDirectory(Array<String>& FilesArray);
	static void GetAllFilesInDirectory(const String& DirectoryName, Array<String>& FilesArray);

private:
	static String BaseDirectoryName;
};

