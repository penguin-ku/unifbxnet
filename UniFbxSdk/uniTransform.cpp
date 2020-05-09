#include "uniTransform.h"


void ParseTransform(const FbxNode * const pFbxTransform, UniTransform& uniTransform)
{
	const FbxVector4 lT = pFbxTransform->LclTranslation.Get();
	const FbxVector4 lR = pFbxTransform->LclRotation.Get();
	const FbxVector4 lS = pFbxTransform->LclScaling.Get();
	FbxMatrix matrixGeo;
	matrixGeo.SetIdentity();
	matrixGeo.SetTRS(lT, lR, lS);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			uniTransform.mm[i * 4 + j] = matrixGeo.Get(i, j);
		}
	}
}