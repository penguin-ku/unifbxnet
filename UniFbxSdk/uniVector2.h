#pragma once
#include<fbxsdk.h>


struct UniVector2
{
public:
	float mX;
	float mY;
};

void ParseVector2(const FbxVector2 * const pFbxVector2, UniVector2& uniVector2);