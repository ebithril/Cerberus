#include "AssetManager.h"

#include <UString.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

void AssetManager::LoadAssets()
{
	FindFiles("..");	
}

void AssetManager::FindFiles(const String& DirectoryName)
{
	DIR* Directory = opendir(DirectoryName.CString());
	if (!Directory)
	{
		printf("Directory %s couldn't be opened", DirectoryName.CString());
		return;
	}

	struct dirent* pDirent;
	while ((pDirent = readdir(Directory)) != nullptr)
	{
		if (pDirent->d_name == "." || pDirent->d_name == "..")
		{
			printf("actually return");
			continue;
		}

		printf("%s\n", pDirent->d_name);

		struct stat buffer;
		int status = stat(pDirent->d_name, &buffer);

		if (status == 0)
		{
			if (S_ISDIR(buffer.st_mode))
			{
				String NewDir = DirectoryName;
				NewDir += pDirent->d_name;
				FindFiles(NewDir);
			}
		}
	}
}

void AssetManager::LoadFragmentShader(VulkanFragmentShader& Shader, const String& Path)
{
}

void AssetManager::LoadVertexShader(VulkanVertexShader& Shader, const String& Path)
{
}

