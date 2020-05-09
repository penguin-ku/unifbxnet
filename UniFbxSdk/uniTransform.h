#pragma once
#include<fbxsdk.h>

struct UniTransform
{
public:
	double mm[16];
};

void ParseTransform(const FbxNode * const pFbxTransform, UniTransform& uniTransform);