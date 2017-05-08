#include "VulkanLoader.h"

#include "VulkanLoadMacros.h"

#include <stdio.h>

PFN_vkGetInstanceProcAddr VulkanLoader::vkGetProcAddress = NULL;

void VulkanLoader::LoadFunctions()
{

}