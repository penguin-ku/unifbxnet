#pragma once
#include "uniColor.h"
#include "uniVector3.h"
#include "uniVector2.h"

struct UniVertex
{
public:
	UniVector3 mPosition;
	UniVector2 mUV;
	UniVector3 mNormal;
	UniColor mColor;
};