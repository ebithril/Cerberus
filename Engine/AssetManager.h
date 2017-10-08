#pragma once

#include "Asset.h"
#include <Array.h>
#include <UString.h>

class BaseAssetPtr
{
private:
	String AssetName;
	String AssetPath;
};

class AssetManager
{
public:
	static Asset* Load(BaseAssetPtr* AssetPtr);

private:
	Array<Asset*> Assets;	
};

template<typename AssetType>
class AssetPtr : public BaseAssetPtr
{
public:
	AssetType* Get() 
	{
		if (Asset)
		{
			return Asset;
		}
		
		Load();

		return Asset;
	}

	void Load()
	{
		Asset = dynamic_cast<AssetType>(AssetManager::Load(this));
	}

private:
	AssetType* Asset;
};

