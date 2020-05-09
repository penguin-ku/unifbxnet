#include "uniMaterial.h"

void ParseMaterial(const FbxSurfaceMaterial * const pFbxMaterial, UniMaterial& uniMaterial)
{
	if (pFbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
	{
		std::string name = FbxStr2StdStr(pFbxMaterial->GetNameOnly());
		uniMaterial.iNameLength = name.length();
		memset(uniMaterial.mName, 0, sizeof(uniMaterial.mName));
		strcpy(uniMaterial.mName, name.c_str());

		//memset(uniMaterial.mName, 0, sizeof(uniMaterial.mName));
		//memcpy(uniMaterial.mName, name.c_str(), name.length());

		uniMaterial.mShaderType = 0;
		FbxSurfacePhong* phong = (FbxSurfacePhong*)pFbxMaterial;
		ParseColor(&phong->Ambient.Get(), uniMaterial.mAmbient);
		uniMaterial.mAmbientFactor = (float)phong->AmbientFactor.Get();
		ParseColor(&phong->Diffuse.Get(), uniMaterial.mDiffuse);
		uniMaterial.mDiffuseFactor = (float)phong->DiffuseFactor.Get();
		ParseColor(&phong->Specular.Get(), uniMaterial.mSpecular);
		uniMaterial.mSpecularFactor = (float)phong->SpecularFactor.Get();
		ParseColor(&phong->Emissive.Get(), uniMaterial.mEmissive);
		uniMaterial.mEmissiveFactor = (float)phong->EmissiveFactor.Get();
		ParseColor(&phong->TransparentColor.Get(), uniMaterial.mTransparentColor);
		uniMaterial.mTransparencyFactor = (float)phong->TransparencyFactor.Get();
		ParseColor(&phong->Reflection.Get(), uniMaterial.mReflection);
		uniMaterial.mReflectionFactor = (float)phong->ReflectionFactor.Get();
		ParseColor(&phong->Bump.Get(), uniMaterial.mBump);
		uniMaterial.mBumpFactor = (float)phong->BumpFactor.Get();
		ParseColor(&phong->NormalMap.Get(), uniMaterial.mNormalMap);

		uniMaterial.mShininess = (float)phong->Shininess.Get();

		FbxTexture* pTexture = phong->Diffuse.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pDiffuseTexture);
		}
		pTexture = phong->Emissive.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pEmissiveTexture);
		}
		pTexture = phong->Ambient.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pAmbientTexture);
		}
		pTexture = phong->Specular.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pSpecularTexture);
		}
		pTexture = phong->Reflection.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pReflectionTexture);
		}
		pTexture = phong->Bump.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pBumpTexture);
		}
		pTexture = phong->NormalMap.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pNormalTexture);
		}
	}
	else if (pFbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
	{
		std::string name = FbxStr2StdStr(pFbxMaterial->GetNameOnly());
		memset(uniMaterial.mName, 0, sizeof(uniMaterial.mName));
		memcpy(uniMaterial.mName, name.c_str(), name.length());

		uniMaterial.mShaderType = 1;
		FbxSurfaceLambert* lambert = (FbxSurfaceLambert*)pFbxMaterial;
		ParseColor(&lambert->Ambient.Get(), uniMaterial.mAmbient);
		uniMaterial.mAmbientFactor = (float)lambert->AmbientFactor.Get();
		ParseColor(&lambert->Diffuse.Get(), uniMaterial.mDiffuse);
		uniMaterial.mDiffuseFactor = (float)lambert->DiffuseFactor.Get();
		ParseColor(&lambert->Emissive.Get(), uniMaterial.mEmissive);
		uniMaterial.mEmissiveFactor = (float)lambert->EmissiveFactor.Get();
		ParseColor(&lambert->TransparentColor.Get(), uniMaterial.mTransparentColor);
		uniMaterial.mTransparencyFactor = (float)lambert->TransparencyFactor.Get();
		ParseColor(&lambert->Bump.Get(), uniMaterial.mBump);
		uniMaterial.mBumpFactor = (float)lambert->BumpFactor.Get();
		ParseColor(&lambert->NormalMap.Get(), uniMaterial.mNormalMap);

		FbxTexture* pTexture = lambert->Diffuse.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pDiffuseTexture);
		}
		pTexture = lambert->Emissive.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pEmissiveTexture);
		}
		pTexture = lambert->Ambient.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pAmbientTexture);
		}
		pTexture = lambert->Bump.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pBumpTexture);
		}
		pTexture = lambert->NormalMap.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			ParseTexture(pTexture, uniMaterial.pNormalTexture);
		}
	}
}