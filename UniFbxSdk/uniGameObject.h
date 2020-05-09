#pragma once
#include <string>
#include<fbxsdk.h>
#include "uniTransform.h"
#include "uniMesh.h"
#include"uniGeoTransform.h"
#include"uniMaterial.h"
#include "common.h"

struct UniGameObject
{
public:
	int iNameLength;
	char mName[128];
	UniTransform mTransform;
	UniGeoTransform mGeometryTransform;
};




