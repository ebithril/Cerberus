#include "Filesystem.h"

#include <SDL2/SDL_filesystem.h>

void FileSystem::InitBaseDirectory()
{
	BaseDirectoryName = SDL_GetBasePath();
}

void FileSystem::GetAllFilesInDirectory(Array<String>& FilesArray)
{
	GetAllFilesInDirectory(BaseDirectoryName, FilesArray);
}

void FileSystem::GetAllFilesInDirectory(const String& DirectoryName, Array<String>& FilesArray)
{
	
}

