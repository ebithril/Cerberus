#include "VulkanFragmentShader.h"

#include <stdio.h>

void VulkanFragmentShader::LoadShader(const int8* ShaderFileName)
{
	Array<int8> Glsl;
	FILE* file = fopen(ShaderFileName, "r");

	Array<uint32> Spirv = CompileGLSL(ShaderFileName, ShaderType::FragmentShader, Glsl);
}
