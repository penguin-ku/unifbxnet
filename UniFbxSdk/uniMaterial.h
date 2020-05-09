#pragma once
#include <string>
#include<fbxsdk.h>
#include"uniColor.h"
#include "uniTexture.h"


struct UniMaterial
{
public:
	int iNameLength;
	char mName[64];
	int mShaderType;// 0 Phong£¬ 1 Lambert
	UniColor mAmbient;
	float mAmbientFactor;
	UniTexture pAmbientTexture;
	UniColor mDiffuse;
	float mDiffuseFactor;
	UniTexture pDiffuseTexture;
	UniColor mSpecular;
	float mSpecularFactor;
	UniTexture pSpecularTexture;
	UniColor mEmissive;
	UniTexture pEmissiveTexture;
	float mEmissiveFactor;
	UniColor mTransparentColor;
	float mTransparencyFactor;
	UniColor mReflection;
	float mReflectionFactor;
	UniTexture pReflectionTexture;
	float mShininess;
	UniColor mNormalMap;
	UniTexture pNormalTexture;
	UniColor mBump;
	float mBumpFactor;
	UniTexture pBumpTexture;
};

void ParseMaterial(const FbxSurfaceMaterial * const pFbxMaterial, UniMaterial& uniMaterial);
