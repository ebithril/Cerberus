#pragma once

#include "EngineStructs.h"
#include "Asset.h"

#include <Array.h>

class String;

enum class ShaderType : uint8
{
	VertexShader,
	FragmentShader
};

class VulkanShader : public Asset
{
public:	
	virtual void LoadShader(const String& ShaderFileName) = 0;

	virtual void BindShader() = 0;

protected:
	Array<uint32> CompileGLSL(const String& ShaderFileName, ShaderType Type, const Array<int8>& Data);

};
