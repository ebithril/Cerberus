#include "VulkanFragmentShader.h"

#include <FileOperations.h>

void VulkanFragmentShader::LoadShader(const String& ShaderFileName)
{
	Array<int8> Glsl;
	ReadFileIntoArray(ShaderFileName, Glsl);

	Array<uint32> Spirv = CompileGLSL(ShaderFileName, ShaderType::FragmentShader, Glsl);
}

