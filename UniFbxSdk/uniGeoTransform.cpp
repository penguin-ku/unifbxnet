#include "uniGeoTransform.h"


void ParseGeoTransform(const FbxNode * const pFbxTransform, UniGeoTransform& uniTransform)
{
	const FbxVector4 lT = pFbxTransform->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 lR = pFbxTransform->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 lS = pFbxTransform->GetGeometricScaling(FbxNode::eSourcePivot);
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