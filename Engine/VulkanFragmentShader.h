#pragma once

#include "VulkanShader.h"

class VulkanFragmentShader : public VulkanShader
{
public:
	virtual void LoadShader(const int8* ShaderFileName) override;

private:

};