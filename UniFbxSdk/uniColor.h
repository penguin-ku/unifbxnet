#pragma once

#include <fbxsdk.h>

struct UniColor
{
public:
	float mRed;
	float mGreen;
	float mBlue;
	float mAlpha;
};

void ParseColor(const FbxColor * const pvector4, UniColor& color);
void ParseColor(const FbxDouble3 * const pvector4, UniColor& color);