#include "uniColor.h"


void ParseColor(const FbxColor * const pvector4, UniColor& color)
{
	color.mRed = (float)pvector4->mRed;
	color.mGreen = (float)pvector4->mGreen;
	color.mBlue = (float)pvector4->mBlue;
	color.mAlpha = (float)pvector4->mAlpha;
}
void ParseColor(const FbxDouble3 * const pvector4, UniColor& color)
{
	color.mRed = (float)pvector4->mData[0];
	color.mGreen = (float)pvector4->mData[1];
	color.mBlue = (float)pvector4->mData[2];
	color.mAlpha = 1;
}