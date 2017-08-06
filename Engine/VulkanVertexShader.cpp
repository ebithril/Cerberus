#include "VulkanVertexShader.h"

#include <FileOperations.h>

void VulkanVertexShader::LoadShader(const String& ShaderFileName)
{
	Array<int8> Glsl;
	ReadFileIntoArray(ShaderFileName, Glsl);
	Array<uint32> Spirv = CompileGLSL(ShaderFileName, ShaderType::VertexShader, Glsl);
}

