using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace UniFbxSdkNet
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct FbxManagerRef
    {
        public IntPtr ptr;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct FbxNodeRef
    {
        public IntPtr ptr;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct FbxMeshRef
    {
        public IntPtr ptr;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniColor
    {
        public float mRed;
        public float mGreen;
        public float mBlue;
        public float mAlpha;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniVector2
    {
        public float mX;
        public float mY;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniVector3
    {
        public float mX;
        public float mY;
        public float mZ;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniVector4
    {
        public float mX;
        public float mY;
        public float mZ;
        public float mW;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniVertex
    {
        public UniVector3 mPosition;
        public UniVector2 mUV;
        public UniVector3 mNormal;
        public UniColor mColor;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniTexture
    {
        public int mTextureType;
        public bool mSwapUV;
        public UniVector2 mTranslation;
        public UniVector2 mScale;
        public UniVector3 mRotation;
        public int iRelativeLength;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] mRelativePath;
        public int iFileLength;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] mFilePath;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniTransform
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public double[] mm;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniGeoTransform
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public double[] mm;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public class UniPolygon
    {
        public int mMaterialID;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public UniVertex[] mVertices;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniMaterial
    {
        public int iNameLength;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] mName;
        public int mShaderType;// 0 Phong， 1 Lambert
        public UniColor mAmbient;
        public float mAmbientFactor;
        public UniTexture pAmbientTexture;
        public UniColor mDiffuse;
        public float mDiffuseFactor;
        public UniTexture pDiffuseTexture;
        public UniColor mSpecular;
        public float mSpecularFactor;
        public UniTexture pSpecularTexture;
        public UniColor mEmissive;
        public UniTexture pEmissiveTexture;
        public float mEmissiveFactor;
        public UniColor mTransparentColor;
        public float mTransparencyFactor;
        public UniColor mReflection;
        public float mReflectionFactor;
        public UniTexture pReflectionTexture;
        public float mShininess;
        public UniColor mNormalMap;
        public UniTexture pNormalTexture;
        public UniColor mBump;
        public float mBumpFactor;
        public UniTexture pBumpTexture;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct UniGameObject
    {
        public int iNameLength;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] mName;
        public UniTransform mTransform;
        public UniGeoTransform mGeometryTransform;
    }

    public static partial class UniFbxSdkRef
    {
        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Load(byte[] path, ref FbxManagerRef fbxManagerRef, ref FbxNodeRef fbxNodeRef);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Destroy(FbxManagerRef fbxManagerRef);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetGameObject(FbxNodeRef fbxNodeRef, ref UniGameObject uniGameObject);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetMesh(FbxNodeRef fbxNodeRef, ref FbxMeshRef fbxMeshRef);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetPolygonCount(FbxMeshRef fbxMeshRef);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetPolygons(FbxMeshRef fbxMeshRef, int polygonCount, IntPtr polygons);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetMaterialCount(FbxNodeRef fbxNodeRef);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool GetMaterials(FbxNodeRef fbxNodeRef, int count, IntPtr uniMaterial);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetChildrenCount(FbxNodeRef fbxNodeRef);

        [DllImport("UniFbxSdk.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool GetChildrenNodes(FbxNodeRef fbxNodeRef, int childCount, IntPtr childRefs);

        /// <summary>
        /// 获取材质
        /// </summary>
        /// <param name="fbxNodeRef"></param>
        /// <returns></returns>
        public static UniMaterial[] GetMaterials(FbxNodeRef fbxNodeRef)
        {
            int materialCount = UniFbxSdkRef.GetMaterialCount(fbxNodeRef);
            if (materialCount > 0)
            {
                int size = Marshal.SizeOf(typeof(UniMaterial)) * materialCount;
                IntPtr pBuff = Marshal.AllocHGlobal(size); //直接分配childrenCount个元素的空间
                bool res = UniFbxSdkRef.GetMaterials(fbxNodeRef, materialCount, pBuff);
                UniMaterial[] materials = new UniMaterial[materialCount];
                for (int i = 0; i < materialCount; i++)
                {
                    IntPtr ptr = new IntPtr(pBuff.ToInt64() + Marshal.SizeOf(typeof(UniMaterial)) * i);
                    materials[i] = (UniMaterial)Marshal.PtrToStructure(ptr, typeof(UniMaterial));
                }
                Marshal.FreeHGlobal(pBuff); //释放内存
                return materials;
            }
            else
            {
                return new UniMaterial[0];
            }
        }

        /// <summary>
        /// 获取子节点
        /// </summary>
        /// <param name="fbxNodeRef"></param>
        /// <returns></returns>
        public static FbxNodeRef[] GetChildrenNodes(FbxNodeRef fbxNodeRef)
        {
            int childrenCount = UniFbxSdkRef.GetChildrenCount(fbxNodeRef);
            if (childrenCount > 0)
            {
                int size = Marshal.SizeOf(typeof(FbxNodeRef)) * childrenCount;
                IntPtr pBuff = Marshal.AllocHGlobal(size); //直接分配childrenCount个元素的空间
                bool res = UniFbxSdkRef.GetChildrenNodes(fbxNodeRef, childrenCount, pBuff);
                FbxNodeRef[] childrenNodes = new FbxNodeRef[childrenCount];
                for (int i = 0; i < childrenCount; i++)
                {
                    IntPtr ptr = new IntPtr(pBuff.ToInt64() + Marshal.SizeOf(typeof(FbxNodeRef)) * i);
                    childrenNodes[i] = (FbxNodeRef)Marshal.PtrToStructure(ptr, typeof(FbxNodeRef));
                }
                Marshal.FreeHGlobal(pBuff); //释放内存
                return childrenNodes;
            }
            else
            {
                return new FbxNodeRef[0];
            }
        }

        /// <summary>
        /// 获取多边形
        /// </summary>
        /// <param name="fbxNodeRef"></param>
        /// <returns></returns>
        public static UniPolygon[] GetPolygons(FbxNodeRef fbxNodeRef)
        {
            FbxMeshRef fbxMeshRef = default(FbxMeshRef);
            UniFbxSdkRef.GetMesh(fbxNodeRef, ref fbxMeshRef);
            int polygonCount = UniFbxSdkRef.GetPolygonCount(fbxMeshRef);

            if (polygonCount > 0)
            {
                int size = Marshal.SizeOf(typeof(UniPolygon)) * polygonCount;
                IntPtr pBuff = Marshal.AllocHGlobal(size); //直接分配childrenCount个元素的空间
                bool res = UniFbxSdkRef.GetPolygons(fbxMeshRef, polygonCount, pBuff);
                UniPolygon[] polygons = new UniPolygon[polygonCount];
                for (int i = 0; i < polygonCount; i++)
                {
                    IntPtr ptr = new IntPtr(pBuff.ToInt64() + Marshal.SizeOf(typeof(UniPolygon)) * i);
                    polygons[i] = (UniPolygon)Marshal.PtrToStructure(ptr, typeof(UniPolygon));
                }
                Marshal.FreeHGlobal(pBuff); //释放内存
                return polygons;
            }
            else
            {
                return new UniPolygon[0];
            }
        }
    }
}


