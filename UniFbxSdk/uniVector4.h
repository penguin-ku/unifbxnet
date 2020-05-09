#pragma once
#include<fbxsdk.h>

struct UniVector4
{
public:
	float mX;
	float mY;
	float mZ;
	float mW;
};

void ParseVector4(const FbxVector4 * const pFbxVector4, UniVector4& uniVector4);