#include "VulkanShader.h"

#include <shaderc/shaderc.hpp>
#include <UString.h>

shaderc_shader_kind GetKindFromType(ShaderType Type)
{
	switch (Type)
	{
	case ShaderType::VertexShader:
		return shaderc_glsl_vertex_shader;
	case ShaderType::FragmentShader:
		return shaderc_glsl_fragment_shader;
	}

	return shaderc_glsl_vertex_shader;
}

Array<uint32> VulkanShader::CompileGLSL(const String& ShaderFileName, ShaderType Type, const Array<int8>& Data)
{
	shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	shaderc_shader_kind Kind = GetKindFromType(Type);

	shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(Data.Data(), Data.Num(), Kind, ShaderFileName.CString(), options);

	Array<uint32> CompiledShader;
	for (auto& part : module)
	{
		CompiledShader.Add(part);
	}

	return CompiledShader;
}
