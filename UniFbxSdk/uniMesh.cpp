#include "uniMesh.h"



bool GetPolygons(FbxMesh* pMesh, int polygonCount, UniPolygon uniPolygons[])
{
	if (!pMesh)
	{
		return false;
	}
	const FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial();
	FbxVector4* pCtrlPoints = pMesh->GetControlPoints();
	const FbxGeometryElementUV* lUVElement = pMesh->GetElementUV(0);
	const FbxGeometryElementNormal* lNormalElement = pMesh->GetElementNormal();
	const FbxGeometryElementVertexColor* lColorElement = pMesh->GetElementVertexColor();

	int vertexCounter = 0;
	for (int polygonIndex = 0; polygonIndex < polygonCount; polygonIndex++)
	{
		// ��ȡ����
		if (lMaterialElement)
		{
			if (lMaterialElement->GetMappingMode() == FbxGeometryElement::eByPolygon)// ÿ������ε���ָ������
			{
				uniPolygons[polygonIndex].mMaterialID = lMaterialElement->GetIndexArray().GetAt(polygonIndex);
			}
			else if (lMaterialElement->GetMappingMode() == FbxGeometryElement::eAllSame)// ���ж����һ��ָ������ͬһ������
			{
				uniPolygons[polygonIndex].mMaterialID = lMaterialElement->GetIndexArray().GetAt(0);
			}
		}
		else
		{
			uniPolygons[polygonIndex].mMaterialID = -1;
		}

		int verticesCount = pMesh->GetPolygonSize(polygonIndex);
		if (verticesCount > 0)
		{
			for (int pointIndex = 0; pointIndex < verticesCount && pointIndex < 3; pointIndex++)// �˴�ֻ֧�����ǻ���fbx����ȥ����δ���ǻ���fbx��̫�˷�����
			{
				// ��ȡ����
				if (pCtrlPoints)
				{
					int lPolyVertIndex = pMesh->GetPolygonVertex(polygonIndex, pointIndex);
					// read control vertex position
					FbxVector4 position = pCtrlPoints[lPolyVertIndex];
					ParseVector3(&position, uniPolygons[polygonIndex].pVertices[pointIndex].mPosition);
				}

				// ��ȡuv
				if (lUVElement)
				{
					if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
					{
						int lPolyVertIndex = pMesh->GetPolygonVertex(polygonIndex, pointIndex);
						if (lUVElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						{
							FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(lPolyVertIndex);
							ParseVector2(&lUVValue, uniPolygons[polygonIndex].pVertices[pointIndex].mUV);
						}
						else if (lUVElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						{
							int id = lUVElement->GetIndexArray().GetAt(lPolyVertIndex);
							FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(id);
							ParseVector2(&lUVValue, uniPolygons[polygonIndex].pVertices[pointIndex].mUV);
						}
					}
					else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
					{
						int lTextureUVIndex = pMesh->GetTextureUVIndex(polygonIndex, pointIndex);

						FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(lTextureUVIndex);
						ParseVector2(&lUVValue, uniPolygons[polygonIndex].pVertices[pointIndex].mUV);
					}
				}

				// ��ȡ����
				if (lNormalElement)
				{
					if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
					{
						int lNormalIndex = lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect ? vertexCounter :
							lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lNormalIndex = lNormalElement->GetIndexArray().GetAt(vertexCounter) : 0;
						FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
						ParseVector3(&lNormal, uniPolygons[polygonIndex].pVertices[pointIndex].mNormal);
					}
				}

				// ��ȡ��ɫ
				if (lColorElement)
				{
					if (lColorElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
					{
						int lPolyVertIndex = pMesh->GetPolygonVertex(polygonIndex, pointIndex);
						int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect ? lPolyVertIndex :
							lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(lPolyVertIndex) : 0;

						FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
						ParseColor(&lColor, uniPolygons[polygonIndex].pVertices[pointIndex].mColor);
					}
					else if (lColorElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
					{
						int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect ? vertexCounter :
							lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(vertexCounter) : 0;

						FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
						ParseColor(&lColor, uniPolygons[polygonIndex].pVertices[pointIndex].mColor);
					}
				}
				else
				{
					uniPolygons[polygonIndex].pVertices[pointIndex].mColor.mAlpha = 1;
					uniPolygons[polygonIndex].pVertices[pointIndex].mColor.mBlue = 1;
					uniPolygons[polygonIndex].pVertices[pointIndex].mColor.mRed = 1;
					uniPolygons[polygonIndex].pVertices[pointIndex].mColor.mGreen = 1;
				}

				vertexCounter++;
			}
		}
	}
}
//
//int GetPolygonSize(FbxMesh* pMesh, int polygonIndex)
//{
//	if (!pMesh)
//	{
//		return 0;
//	}
//	return pMesh->GetPolygonSize(polygonIndex);
//}
//
//bool GetPolygonMaterialID(FbxMesh* pMesh, int polygonIndex, int& materialID)
//{
//	if (!pMesh)
//	{
//		return false;
//	}
//	const FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial();
//
//	if (lMaterialElement)
//	{
//		if (lMaterialElement->GetMappingMode() == FbxGeometryElement::eByPolygon)// ÿ������ε���ָ������
//		{
//			materialID = lMaterialElement->GetIndexArray().GetAt(polygonIndex);
//		}
//		else if (lMaterialElement->GetMappingMode() == FbxGeometryElement::eAllSame)// ���ж����һ��ָ������ͬһ������
//		{
//			materialID = lMaterialElement->GetIndexArray().GetAt(0);
//		}
//	}
//	else
//	{
//		materialID = -1;
//	}
//
//	return true;
//}
//
//// refrence:http://help.autodesk.com/view/FBX/2020/ENU/?guid=FBX_Developer_Help_cpp_ref_import_scene_2_display_mesh_8cxx_example_html
//bool GetPolygonVertex(FbxMesh* pMesh, int polygonIndex, int pointIndex, UniVertex& uniVertex)
//{
//	if (!pMesh)
//	{
//		return false;
//	}
//
//	int vertexCounter = 0;
//	for (size_t i = 0; i < pMesh->GetPolygonCount() && i < polygonIndex; i++)
//	{
//		vertexCounter += pMesh->GetPolygonSize(i);
//	}
//	vertexCounter += pointIndex;
//
//	// ��ȡ���Ƶ�
//	FbxVector4* pCtrlPoints = pMesh->GetControlPoints();
//	if (pCtrlPoints)
//	{
//		int lPolyVertIndex = pMesh->GetPolygonVertex(polygonIndex, pointIndex);
//		// read control vertex position
//		FbxVector4 position = pCtrlPoints[lPolyVertIndex];
//		ParseVector3(&position, uniVertex.mPosition);
//	}
//
//	// ��ȡUV
//	const FbxGeometryElementUV* lUVElement = pMesh->GetElementUV(0);
//	if (lUVElement)
//	{
//		if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//		{
//			int lPolyVertIndex = pMesh->GetPolygonVertex(polygonIndex, pointIndex);
//			if (lUVElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//			{
//				FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(lPolyVertIndex);
//				ParseVector2(&lUVValue, uniVertex.mUV);
//			}
//			else if(lUVElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//			{
//				int id = lUVElement->GetIndexArray().GetAt(lPolyVertIndex);
//				FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(id);
//				ParseVector2(&lUVValue, uniVertex.mUV);
//			}
//		}
//		else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//		{
//			int lTextureUVIndex = pMesh->GetTextureUVIndex(polygonIndex, pointIndex);
//
//			FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(lTextureUVIndex);
//			ParseVector2(&lUVValue, uniVertex.mUV);
//
//		}
//	}
//
//	// ��ȡnormal
//	const FbxGeometryElementNormal* lNormalElement = pMesh->GetElementNormal();
//	if (lNormalElement)
//	{
//		if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//		{
//			int lNormalIndex = lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect ? vertexCounter :
//				lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lNormalIndex = lNormalElement->GetIndexArray().GetAt(vertexCounter) : 0;
//			FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
//			ParseVector3(&lNormal, uniVertex.mNormal);
//		}
//
//	}
//
//	// ��ȡ������ɫ
//	const FbxGeometryElementVertexColor* lColorElement = pMesh->GetElementVertexColor();
//	if (lColorElement)
//	{
//		if (lColorElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//		{
//			int lPolyVertIndex = pMesh->GetPolygonVertex(polygonIndex, pointIndex);
//			int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect ? lPolyVertIndex :
//				lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(lPolyVertIndex) : 0;
//
//			FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
//			ParseColor(&lColor, uniVertex.mColor);
//		}
//		else if (lColorElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//		{
//			int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect ? vertexCounter :
//				lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(vertexCounter) : 0;
//
//			FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
//			ParseColor(&lColor, uniVertex.mColor);
//		}
//	}
//	else
//	{
//		uniVertex.mColor.mAlpha = 1;
//		uniVertex.mColor.mBlue = 1;
//		uniVertex.mColor.mRed = 1;
//		uniVertex.mColor.mGreen = 1;
//	}
//	return true;
//}
//
//bool GetPolygonVertices(FbxMesh* pMesh, int polygonIndex, int pointCount, UniVertex uniVertex[])
//{
//	if (!pMesh)
//	{
//		return false;
//	}
//
//	int vertexCounter = 0;
//	for (int i = 0; i < pMesh->GetPolygonCount() && i < polygonIndex; i++)
//	{
//		vertexCounter += pMesh->GetPolygonSize(i);
//	}
//
//	FbxVector4* pCtrlPoints = pMesh->GetControlPoints();
//	const FbxGeometryElementUV* lUVElement = pMesh->GetElementUV(0);
//	const FbxGeometryElementNormal* lNormalElement = pMesh->GetElementNormal();
//	const FbxGeometryElementVertexColor* lColorElement = pMesh->GetElementVertexColor();
//
//	for (int pointIndex = 0; pointIndex < pointCount; pointIndex++)
//	{
//		int lPolyVertIndex = pMesh->GetPolygonVertex(polygonIndex, pointIndex);
//
//		// ��ȡ���Ƶ�
//		if (pCtrlPoints)
//		{
//			// read control vertex position
//			FbxVector4 position = pCtrlPoints[lPolyVertIndex];
//			ParseVector3(&position, uniVertex[pointIndex].mPosition);
//		}
//
//		// ��ȡUV
//		if (lUVElement)
//		{
//			if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//				if (lUVElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//				{
//					FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(lPolyVertIndex);
//					ParseVector2(&lUVValue, uniVertex[pointIndex].mUV);
//				}
//				else if (lUVElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//				{
//					int id = lUVElement->GetIndexArray().GetAt(lPolyVertIndex);
//					FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(id);
//					ParseVector2(&lUVValue, uniVertex[pointIndex].mUV);
//				}
//			}
//			else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				int lTextureUVIndex = pMesh->GetTextureUVIndex(polygonIndex, pointIndex);
//
//				FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(lTextureUVIndex);
//				ParseVector2(&lUVValue, uniVertex[pointIndex].mUV);
//
//			}
//		}
//
//		// ��ȡnormal
//		if (lNormalElement)
//		{
//			if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				int lNormalIndex = lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect ? vertexCounter :
//					lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lNormalIndex = lNormalElement->GetIndexArray().GetAt(vertexCounter) : 0;
//				FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
//				ParseVector3(&lNormal, uniVertex[pointIndex].mNormal);
//			}
//
//		}
//
//		// ��ȡ������ɫ
//		if (lColorElement)
//		{
//			if (lColorElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//				int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect ? lPolyVertIndex :
//					lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(lPolyVertIndex) : 0;
//
//				FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
//				ParseColor(&lColor, uniVertex[pointIndex].mColor);
//			}
//			else if (lColorElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect ? vertexCounter :
//					lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(vertexCounter) : 0;
//
//				FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
//				ParseColor(&lColor, uniVertex[pointIndex].mColor);
//			}
//		}
//		else
//		{
//			uniVertex[pointIndex].mColor.mAlpha = 1;
//			uniVertex[pointIndex].mColor.mBlue = 1;
//			uniVertex[pointIndex].mColor.mRed = 1;
//			uniVertex[pointIndex].mColor.mGreen = 1;
//		}
//
//		vertexCounter++;
//	}
//	return true;
//}
//
