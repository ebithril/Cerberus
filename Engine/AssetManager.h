#pragma once

#include <Array.h>

class VulkanFragmentShader;
class VulkanVertexShader;
class String;

class AssetManager
{
public:
	static void LoadAssets();
	static void FindFiles(const String& DirectoryName);

private:
	static void LoadFragmentShader(VulkanFragmentShader& Shader, const String& Path);
	static void LoadVertexShader(VulkanVertexShader& Shader, const String& Path);

};

