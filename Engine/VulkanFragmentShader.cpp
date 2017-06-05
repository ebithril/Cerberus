#include "VulkanFragmentShader.h"

void VulkanFragmentShader::LoadShader(const int8* ShaderFileName)
{
	Array<int8> Glsl;
	Array<uint32> Spirv = CompileGLSL(ShaderFileName, ShaderType::FragmentShader, Glsl);
}