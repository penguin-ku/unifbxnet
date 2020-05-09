#pragma once

#include <fbxsdk.h>
#include<string>

#define MAX_MATERIAL_CHANNEL_COUNT 24
#define UV_SET_COUNT 4

struct FbxManagerRef
{
public:
	void* ptr;
};

struct FbxNodeRef
{
public:
	void* ptr;
};

struct FbxMeshRef
{
public:
	void* ptr;
};

char* StdStr2FbxStr1(std::string str);
FbxString StdStr2FbxStr(std::string str);
std::string FbxStr2StdStr(FbxString fbxStr);