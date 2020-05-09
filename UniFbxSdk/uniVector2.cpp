#include "uniVector2.h"

void ParseVector2(const FbxVector2 * const pFbxVector2, UniVector2& uniVector2)
{
	uniVector2.mX = (float)pFbxVector2->mData[0];
	uniVector2.mY = (float)pFbxVector2->mData[1];
}