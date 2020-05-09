#include "uniVector3.h"

void ParseVector3(const FbxVector4 * const pFbxVector4, UniVector3&  uniVector3)
{
	uniVector3.mX = (float)pFbxVector4->mData[0];
	uniVector3.mY = (float)pFbxVector4->mData[1];
	uniVector3.mZ = (float)pFbxVector4->mData[2];
}