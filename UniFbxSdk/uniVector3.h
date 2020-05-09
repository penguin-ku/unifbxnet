#pragma once
#include<fbxsdk.h>

struct UniVector3
{
public:
	float mX;
	float mY;
	float mZ;
};

void ParseVector3(const FbxVector4 * const pFbxVector4, UniVector3&  uniVector3);