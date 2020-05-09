#pragma once

#include <string>
#include<fbxsdk.h>
#include"uniColor.h"
#include"uniVector2.h"
#include"uniVector3.h"
#include"uniVector4.h"
#include "common.h"

struct UniTexture
{
public:
	int mTextureType;
	bool mSwapUV;
	UniVector2 mTranslation;
	UniVector2 mScale;
	UniVector3 mRotation;
	int iRelativeLength;
	char mRelativePath[256];
	int iFileLength;
	char mFilePath[256];
};

void ParseTexture(const FbxTexture * const ptexture, UniTexture& texture);
