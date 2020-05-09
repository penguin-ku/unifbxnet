#include "uniVector4.h"

void ParseVector4(const FbxVector4 * const pFbxVector4, UniVector4& uniVector4)
{
	uniVector4.mX = (float)pFbxVector4->mData[0];
	uniVector4.mY = (float)pFbxVector4->mData[1];
	uniVector4.mZ = (float)pFbxVector4->mData[2];
	uniVector4.mW = (float)pFbxVector4->mData[3];
}