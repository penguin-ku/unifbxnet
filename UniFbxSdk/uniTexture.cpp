#include "uniTexture.h"


void ParseTexture(const FbxTexture * const ptexture, UniTexture& texture)
{
	//std::string name = FbxStr2StdStr(ptexture->GetNameOnly());
	//memset(texture.mName, 0, sizeof(texture.mName));
	//memcpy(texture.mName, name.c_str(), name.length());

	texture.mTextureType = 0;
	texture.mSwapUV = ptexture->GetSwapUV();
	texture.mTranslation.mX = (float)ptexture->GetTranslationU();
	texture.mTranslation.mY = (float)ptexture->GetTranslationV();
	texture.mScale.mX = (float)ptexture->GetScaleU();
	texture.mScale.mY = (float)ptexture->GetScaleV();
	texture.mRotation.mX = (float)ptexture->GetRotationU();
	texture.mRotation.mY = (float)ptexture->GetRotationV();
	texture.mRotation.mZ = (float)ptexture->GetRotationW();

	if (ptexture->Is<FbxFileTexture>())
	{
		FbxFileTexture* fileTexture = (FbxFileTexture*)ptexture;

		std::string relativePath = FbxStr2StdStr(fileTexture->GetRelativeFileName());
		texture.iRelativeLength = relativePath.length();
		memset(texture.mRelativePath, 0, sizeof(texture.mRelativePath));
		strcpy(texture.mRelativePath, relativePath.c_str());


		//memcpy(texture.mRelativePath, relativePath.c_str(), relativePath.length());

		std::string filePath = FbxStr2StdStr(fileTexture->GetFileName());
		texture.iFileLength = filePath.length();
		memset(texture.mFilePath, 0, sizeof(texture.mFilePath));
		strcpy(texture.mFilePath, filePath.c_str());

		//memset(texture.mFilePath, 0, sizeof(texture.mFilePath));
		//memcpy(texture.mFilePath, filePath.c_str(), filePath.length());

	}
	else if (ptexture->Is<FbxLayeredTexture>())
	{
		FbxLayeredTexture* fileTexture = (FbxLayeredTexture*)ptexture;
		throw;
	}
	else if (ptexture->Is<FbxProceduralTexture>())
	{
		FbxProceduralTexture* fileTexture = (FbxProceduralTexture*)ptexture;
		throw;
	}
}
