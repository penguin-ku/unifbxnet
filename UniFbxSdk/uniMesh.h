#pragma once
#include <string>
#include <fbxsdk.h>
#include "common.h"
#include "uniPolygon.h"

//int GetPolygonSize(FbxMesh* pMesh, int polygonIndex);
//
//bool GetPolygonMaterialID(FbxMesh* pMesh, int polygonIndex, int& materialID);
//
//bool GetPolygonVertex(FbxMesh* pMesh, int polygonIndex, int pointIndex, UniVertex& uniVertex);
//
//bool GetPolygonVertices(FbxMesh* pMesh, int polygonIndex, int pointCount, UniVertex uniVertex[]);


bool GetPolygons(FbxMesh* pMesh, int polygonCount, UniPolygon uniPolygons[]);