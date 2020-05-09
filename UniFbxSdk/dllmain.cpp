// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include"uniGameObject.h"
#include <iostream>

// 加载，输出 manager指针，用于后续destroy。以及根节点 rootnode
extern "C" _declspec(dllexport) bool Load(char* pPath, FbxManagerRef& fsManagerRef, FbxNodeRef& fsNodeRef)
{
	std::string strPath = pPath;
	FbxString pFilename = StdStr2FbxStr(pPath);
	FbxManager* pManager = FbxManager::Create();
	FbxIOSettings* pIOS = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(pIOS);
	FbxScene* pScene = FbxScene::Create(pManager, "My Scene");
	FbxImporter* pImporter = FbxImporter::Create(pManager, "");
	if (!pImporter->Initialize(pFilename, -1, pManager->GetIOSettings()))
	{
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", pImporter->GetStatus().GetErrorString());
		return false;
	}

	pImporter->Import(pScene);
	pImporter->Destroy();

	fsManagerRef.ptr = pManager;
	fsNodeRef.ptr = pScene->GetRootNode();

	return true;
}

// 释放
extern "C" _declspec(dllexport) bool Destroy(FbxManagerRef fsManagerRef)
{
	FbxManager* pManager = (FbxManager*)fsManagerRef.ptr;
	if (!pManager)
	{
		return false;
	}
	pManager->Destroy();
	return true;
}

extern "C"  _declspec(dllexport) void GetIntArray(int count, int data[])
{
	for (int i = 0; i < count; i++)
	{
		data[i] = i;
	}
}

// 转述成GameObject
extern "C" _declspec(dllexport) bool GetGameObject(FbxNodeRef fbxNodeRef, UniGameObject& uniGameObject)
{
	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
	if (!pNode)
	{
		uniGameObject.mGeometryTransform.mm[0] = 1;
		uniGameObject.mGeometryTransform.mm[1] = 0;
		uniGameObject.mGeometryTransform.mm[2] = 0;
		uniGameObject.mGeometryTransform.mm[3] = 0;
		uniGameObject.mGeometryTransform.mm[4] = 0;
		uniGameObject.mGeometryTransform.mm[5] = 1;
		uniGameObject.mGeometryTransform.mm[6] = 0;
		uniGameObject.mGeometryTransform.mm[7] = 0;
		uniGameObject.mGeometryTransform.mm[8] = 0;
		uniGameObject.mGeometryTransform.mm[9] = 0;
		uniGameObject.mGeometryTransform.mm[10] = 1;
		uniGameObject.mGeometryTransform.mm[11] = 0;
		uniGameObject.mGeometryTransform.mm[12] = 0;
		uniGameObject.mGeometryTransform.mm[13] = 0;
		uniGameObject.mGeometryTransform.mm[14] = 0;
		uniGameObject.mGeometryTransform.mm[15] = 1;

		uniGameObject.mTransform.mm[0] = 1;
		uniGameObject.mTransform.mm[1] = 0;
		uniGameObject.mTransform.mm[2] = 0;
		uniGameObject.mTransform.mm[3] = 0;
		uniGameObject.mTransform.mm[4] = 0;
		uniGameObject.mTransform.mm[5] = 1;
		uniGameObject.mTransform.mm[6] = 0;
		uniGameObject.mTransform.mm[7] = 0;
		uniGameObject.mTransform.mm[8] = 0;
		uniGameObject.mTransform.mm[9] = 0;
		uniGameObject.mTransform.mm[10] = 1;
		uniGameObject.mTransform.mm[11] = 0;
		uniGameObject.mTransform.mm[12] = 0;
		uniGameObject.mTransform.mm[13] = 0;
		uniGameObject.mTransform.mm[14] = 0;
		uniGameObject.mTransform.mm[15] = 1;
		return false;
	}	
	std::string name = FbxStr2StdStr(pNode->GetNameOnly());
	uniGameObject.iNameLength = name.length();
	memset(uniGameObject.mName, 0, sizeof(uniGameObject.mName));
	strcpy(uniGameObject.mName, name.c_str());

	ParseGeoTransform(pNode, uniGameObject.mGeometryTransform);
	ParseTransform(pNode, uniGameObject.mTransform);
	return true;
}

// 获取子节点个数
extern "C" _declspec(dllexport) int GetChildrenCount(FbxNodeRef fbxNodeRef)
{
	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
	if (!pNode)
	{
		return 0;
	}
	return pNode->GetChildCount();
}

extern "C" _declspec(dllexport) bool GetChildrenNodes(FbxNodeRef fbxNodeRef, int childCount, FbxNodeRef childRef[])
{
	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
	if (!pNode)
	{
		return false;
	}
	for (size_t i = 0; i < childCount; i++)
	{
		childRef[i].ptr = pNode->GetChild(i);
	}

	return true;
}

// 获取所有子节点
extern "C" _declspec(dllexport) bool GetChildNodeByIndex(FbxNodeRef fbxNodeRef, int childIndex, FbxNodeRef& childRef)
{
	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
	if (!pNode)
	{
		return false;
	}
	childRef.ptr = pNode->GetChild(childIndex);

	return true;
}

// 获取材质数
extern "C" _declspec(dllexport) int GetMaterialCount(FbxNodeRef fbxNodeRef)
{
	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
	if (!pNode)
	{
		return 0;
	}
	return pNode->GetMaterialCount();
}

//// 获取材质
//extern "C" _declspec(dllexport) bool GetMaterialByIndex(FbxNodeRef fbxNodeRef, int materialIndex, UniMaterial& uniMaterial)
//{
//	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
//	if (!pNode)
//	{
//		return false;
//	}
//	FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(materialIndex);
//	ParseMaterial(pMaterial, uniMaterial);
//
//	return true;
//}

extern "C" _declspec(dllexport) bool GetMaterials(FbxNodeRef fbxNodeRef, int count, UniMaterial uniMaterial[])
{
	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
	if (!pNode)
	{
		return false;
	}

	for (size_t i = 0; i < count; i++)
	{
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		ParseMaterial(pMaterial, uniMaterial[i]);
	}

	return true;
}


// 获取网格
extern "C" _declspec(dllexport) bool GetMesh(FbxNodeRef fbxNodeRef, FbxMeshRef& fbxMeshRef)
{
	FbxNode* pNode = (FbxNode*)fbxNodeRef.ptr;
	if (!pNode)
	{
		return false;
	}


	fbxMeshRef.ptr = pNode->GetMesh();
	return true;
}

// 获取多边形数
extern "C" _declspec(dllexport) int GetPolygonCount(FbxMeshRef fbxMeshRef)
{
	FbxMesh* pmesh = (FbxMesh*)fbxMeshRef.ptr;
	if (!pmesh)
	{
		return 0;
	}
	return pmesh->GetPolygonCount();
}

extern "C" _declspec(dllexport) bool GetPolygons(FbxMeshRef fbxMeshRef, int polygonCount, UniPolygon uniPolygons[])
{
		FbxMesh* pmesh = (FbxMesh*)fbxMeshRef.ptr;
	if (!pmesh)
	{
		return 0;
	}
	GetPolygons(pmesh, polygonCount, uniPolygons);
}

//// 根据多边形索引获取控制点数
//extern "C" _declspec(dllexport) int GetPolygonSizeByIndex(FbxMeshRef fbxMeshRef, int polygonIndex)
//{
//	FbxMesh* pmesh = (FbxMesh*)fbxMeshRef.ptr;
//	if (!pmesh)
//	{
//		return 0;
//	}
//	return GetPolygonSize(pmesh, polygonIndex);
//}
//
//
//extern "C" _declspec(dllexport) bool GetMaterialByPolygonIndex(FbxMeshRef fbxMeshRef, int polygonIndex, int& materialID)
//{
//	FbxMesh* pmesh = (FbxMesh*)fbxMeshRef.ptr;
//	if (!pmesh)
//	{
//		return false;
//	}
//	return GetPolygonMaterialID(pmesh, polygonIndex, materialID);
//}
//
//extern "C" _declspec(dllexport) bool GetVertexByPolygonIndex(FbxMeshRef fbxMeshRef, int polygonIndex, int pointIndex, UniVertex& uniVertex)
//{
//	FbxMesh* pmesh = (FbxMesh*)fbxMeshRef.ptr;
//	if (!pmesh)
//	{
//		return false;
//	}
//	return GetPolygonVertex(pmesh, polygonIndex, pointIndex, uniVertex);
//
//}
//
//extern "C" _declspec(dllexport) bool GetPolygons(FbxMeshRef fbxMeshRef, int polygonIndex, int verticesCount, UniVertex uniVertex[], int& materialID)
//{
//	FbxMesh* pmesh = (FbxMesh*)fbxMeshRef.ptr;
//	if (!pmesh)
//	{
//		return false;
//	}
//	GetPolygonVertices(pmesh, polygonIndex, verticesCount, uniVertex);
//	GetPolygonMaterialID(pmesh, polygonIndex, materialID);
//}


#ifndef CPP_TEST

void PareseGameObjectByNode(FbxNodeRef fbxNodeRef)
{
	UniGameObject gameObject = UniGameObject();
	GetGameObject(fbxNodeRef, gameObject);

	int materialCount = GetMaterialCount(fbxNodeRef);
	UniMaterial* materials = new UniMaterial[materialCount];
	GetMaterials(fbxNodeRef, materialCount, materials);

	//UniMaterial materials[10];
	//for (int i = 0; i < materialCount; i++)
	//{
	//	GetMaterialByIndex(fbxNodeRef, i, materials[i]);
	//}

	FbxMeshRef fbxMeshRef;
	GetMesh(fbxNodeRef, fbxMeshRef);
	int polygonCount = GetPolygonCount(fbxMeshRef);
	UniPolygon* polygons = new	UniPolygon[polygonCount];
	GetPolygons(fbxMeshRef, polygonCount, polygons);
	//for (int polygonIndex = 0; polygonIndex < polygonCount; polygonIndex++)
	//{
	//	int pointCount = GetPolygonSizeByIndex(fbxMeshRef, polygonIndex);
	//	UniVertex* pVertices = new UniVertex[pointCount];
	//	for (int pointIndex = 0; pointIndex < pointCount; pointIndex++)
	//	{
	//		UniVertex vertex;
	//		GetVertexByPolygonIndex(fbxMeshRef, polygonIndex, pointIndex, vertex);
	//		pVertices[pointIndex] = vertex;
	//	}
	//	int materialID;
	//	GetMaterialByPolygonIndex(fbxMeshRef, polygonIndex, materialID);
	//}

	int childrenCount = GetChildrenCount(fbxNodeRef);
	for (int i = 0; i < childrenCount; i++)
	{
		FbxNodeRef childRef;
		GetChildNodeByIndex(fbxNodeRef, i, childRef);
		PareseGameObjectByNode(childRef);
	}
}


int main()
{
	std::cout << "Hello World!\n";

	FbxManagerRef uniSDkRef = FbxManagerRef();
	FbxNodeRef fbxNodeRef = FbxNodeRef();
	
	Load("F:\\penguin_ku.personal\\unifbxnet\\testmodel\\test202.FBX", uniSDkRef, fbxNodeRef);

	PareseGameObjectByNode(fbxNodeRef);

	Destroy(uniSDkRef);
}
#endif // CPP_TEST
