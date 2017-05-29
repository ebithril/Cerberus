#pragma once

#include "EngineStructs.h"

#include <Array.h>
#include <shaderc/shaderc.hpp>

enum class ShaderType : uint8
{
	VertexShader,
	FragmentShader
};

class VulkanShader
{
public:	
	virtual void LoadShader(const int8* ShaderFileName) = 0;
	static shaderc_shader_kind GetKindFromType(ShaderType Type);

	virtual void BindShader() = 0;

protected:
	Array<uint32> CompileGLSL(const int8* ShaderFileName, ShaderType Type, const Array<int8>& Data);

};
