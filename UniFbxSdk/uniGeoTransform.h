#pragma once
#include<fbxsdk.h>

struct UniGeoTransform
{
public:
	double mm[16];
};

void ParseGeoTransform(const FbxNode * const pFbxTransform, UniGeoTransform& uniTransform);