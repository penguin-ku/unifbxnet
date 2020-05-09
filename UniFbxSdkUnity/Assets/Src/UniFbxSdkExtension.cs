using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace UniFbxSdkNet
{
    public static class UniFbxSdkExtension
    {
        public static Texture2D ToTexture(this UniTexture p_uniTexture, string p_directory)
        {
            string path = string.Format("{0}\\{1}", p_directory, p_uniTexture.mRelativePath.ToString(p_uniTexture.iRelativeLength));
            if (!System.IO.File.Exists(path))
            {
                path = p_uniTexture.mFilePath.ToString(p_uniTexture.iFileLength);// 如果是obj，会保存到此处
                if (!System.IO.File.Exists(path))
                {
                    return null;
                }
            }

            try
            {
                if (!System.IO.File.Exists(path))
                {
                    return null;
                }

                byte[] buffer = System.IO.File.ReadAllBytes(path);
                System.IO.FileInfo file = new System.IO.FileInfo(path);

                Texture2D texture = new Texture2D(1, 1, TextureFormat.RGB24, true);
                texture.LoadImage(buffer);

                return texture;
            }
            catch
            {
                return null;
            }
        }

        public static Color ToColor(this UniColor p_data)
        {
            return new Color(p_data.mRed, p_data.mGreen, p_data.mBlue, p_data.mAlpha);
        }

        public static void ToVector4(this UniVector4 p_data)
        {
            Vector4 p_vector = new Vector4();
            p_data.mX = p_vector.x;
            p_data.mY = p_vector.y;
            p_data.mZ = p_vector.z;
            p_data.mW = p_vector.w;
            return;
        }

        public static Vector3 ToVector3(this UniVector3 p_data)
        {
            return new Vector3(p_data.mX, p_data.mY, p_data.mZ);
        }

        public static Vector2 ToVector2(this UniVector2 p_data)
        {
            return new Vector2(p_data.mX, p_data.mY);
        }

        public static Material ToMaterial(this UniMaterial p_uniMaterial, string p_directory)
        {
            Material material = new Material(Shader.Find("Standard"));
            material.name = p_uniMaterial.mName.ToString(p_uniMaterial.iNameLength);
            material.SetColor("_Color", p_uniMaterial.mDiffuse.ToColor());
            material.SetTexture("_MainTex", p_uniMaterial.pDiffuseTexture.ToTexture(p_directory));

            material.EnableKeyword("_NORMALMAP");
            material.SetFloat("_BumpScale", p_uniMaterial.mBumpFactor);
            material.SetTexture("_BumpMap", p_uniMaterial.pNormalTexture.ToTexture(p_directory));

            return material;
        }

        public static Vertex3 ToVertex(this UniVertex p_vertex)
        {
            return new Vertex3(new Vector3(p_vertex.mPosition.mX, p_vertex.mPosition.mZ, p_vertex.mPosition.mY),
                new Vector2(p_vertex.mUV.mX, p_vertex.mUV.mY),
                new Vector3(p_vertex.mNormal.mX, p_vertex.mNormal.mZ, p_vertex.mNormal.mY),
                new Color(p_vertex.mColor.mRed, p_vertex.mColor.mGreen, p_vertex.mColor.mBlue, p_vertex.mColor.mAlpha));
        }

        //public static Vertex3 ToVertex1(this UniVertex p_vertex)
        //{
        //    return new Vertex3(new Vector3(p_vertex.mPosition.mX, p_vertex.mPosition.mY, -p_vertex.mPosition.mZ),
        //        new Vector2(p_vertex.mUV.mX, p_vertex.mUV.mY),
        //        new Vector3(p_vertex.mNormal.mX, p_vertex.mNormal.mY, -p_vertex.mNormal.mZ),
        //        new Color(p_vertex.mColor.mRed, p_vertex.mColor.mGreen, p_vertex.mColor.mBlue, p_vertex.mColor.mAlpha));
        //}

        public static List<Polygon3> ToPolygon3s(this IEnumerable<UniPolygon> p_polygons)
        {
            return p_polygons.Select(p =>
            {
                return new Polygon3(p.mVertices.Select(v => v.ToVertex()).Reverse().ToArray(), p.mMaterialID);
            }).ToList();
        }

        //public static List<Polygon3> ToPolygon3s1(this IEnumerable<UniPolygon> p_polygons)
        //{
        //    return p_polygons.Select(p =>
        //    {
        //        return new Polygon3(p.mVertices.Select(v => v.ToVertex1()).Reverse().ToArray(), p.mMaterialID);
        //    }).ToList();
        //}

        public static GameObject ToGameObject(this UniGameObjectWrapper p_wrapper, Transform p_parent, string p_directory)
        {
            List<Material> materials = p_wrapper.Materials.Select(p => p.ToMaterial(p_directory)).ToList();
            List<Polygon3> polygons = p_wrapper.Polygons.ToPolygon3s();

            GameObject go = Polygon3.GenerateObject(polygons, materials);
            go.name = p_wrapper.Name;
            if (p_parent != null)
            {
                go.transform.SetParent(p_parent);
            }

            Matrix4x4 matrix = new Matrix4x4()// 转置，神奇的是matrix竟然没提供转置的方法，蛋碎一地
            {
                m00 = (float)p_wrapper.Transform.mm[0],
                m01 = (float)p_wrapper.Transform.mm[4],
                m02 = (float)p_wrapper.Transform.mm[8],
                m03 = (float)p_wrapper.Transform.mm[12],
                m10 = (float)p_wrapper.Transform.mm[1],
                m11 = (float)p_wrapper.Transform.mm[5],
                m12 = (float)p_wrapper.Transform.mm[9],
                m13 = (float)p_wrapper.Transform.mm[13],
                m20 = (float)p_wrapper.Transform.mm[2],
                m21 = (float)p_wrapper.Transform.mm[6],
                m22 = (float)p_wrapper.Transform.mm[10],
                m23 = (float)p_wrapper.Transform.mm[14],
                m30 = (float)p_wrapper.Transform.mm[3],
                m31 = (float)p_wrapper.Transform.mm[7],
                m32 = (float)p_wrapper.Transform.mm[11],
                m33 = (float)p_wrapper.Transform.mm[15]
            };

            Matrix4x4 exchangeYZ = new Matrix4x4()
            {
                m00 = 1,
                m01 = 0,
                m02 = 0,
                m03 = 0,
                m10 = 0,
                m11 = 0,
                m12 = 1,
                m13 = 0,
                m20 = 0,
                m21 = 1,
                m22 = 0,
                m23 = 0,
                m30 = 0,
                m31 = 0,
                m32 = 0,
                m33 = 1
            };
            matrix = exchangeYZ * matrix * exchangeYZ;// YZ轴对换

            go.transform.FromMatrix(matrix);

            //if (p_wrapper.AxisUp == 2)
            //{
            //    if (p_parent != null && p_parent.parent != null)
            //    {
            //        go.transform.position = new Vector3(go.transform.position.x, go.transform.position.z, -go.transform.position.y);
            //    }
            //}

            foreach (var item in p_wrapper.Children)
            {
                GameObject itemChild = item.ToGameObject(go.transform, p_directory);
            }

            return go;
        }

        //public static GameObject ToGameObject1(this UniGameObjectWrapper p_wrapper, Transform p_parent, string p_directory)
        //{
        //    List<Material> materials = p_wrapper.Materials.Select(p => p.ToMaterial(p_directory)).ToList();
        //    List<Polygon3> polygons = p_wrapper.Polygons.ToPolygon3s();

        //    GameObject go = Polygon3.GenerateObject(polygons, materials);
        //    go.name = p_wrapper.Name;
        //    if (p_parent != null)
        //    {
        //        go.transform.SetParent(p_parent);
        //    }
            
        //    Matrix4x4 matrix = new Matrix4x4()// 转置，神奇的是matrix竟然没提供转置的方法，蛋碎一地
        //    {
        //        m00 = (float)p_wrapper.Transform.mm[0],
        //        m01 = (float)p_wrapper.Transform.mm[4],
        //        m02 = -(float)p_wrapper.Transform.mm[8],
        //        m03 = (float)p_wrapper.Transform.mm[12],
        //        m10 = (float)p_wrapper.Transform.mm[1],
        //        m11 = (float)p_wrapper.Transform.mm[5],
        //        m12 = -(float)p_wrapper.Transform.mm[9],
        //        m13 = (float)p_wrapper.Transform.mm[13],
        //        m20 = -(float)p_wrapper.Transform.mm[2],
        //        m21 = -(float)p_wrapper.Transform.mm[6],
        //        m22 = -(float)p_wrapper.Transform.mm[10],
        //        m23 = -(float)p_wrapper.Transform.mm[14],
        //        m30 = (float)p_wrapper.Transform.mm[3],
        //        m31 = (float)p_wrapper.Transform.mm[7],
        //        m32 = -(float)p_wrapper.Transform.mm[11],
        //        m33 = (float)p_wrapper.Transform.mm[15]
        //    };
        //    //Matrix4x4 exchangeYZ = new Matrix4x4()
        //    //{
        //    //    m00 = 1,
        //    //    m01 = 0,
        //    //    m02 = 0,
        //    //    m03 = 0,
        //    //    m10 = 0,
        //    //    m11 = 0,
        //    //    m12 = 1,
        //    //    m13 = 0,
        //    //    m20 = 0,
        //    //    m21 = 1,
        //    //    m22 = 0,
        //    //    m23 = 0,
        //    //    m30 = 0,
        //    //    m31 = 0,
        //    //    m32 = 0,
        //    //    m33 = 1
        //    //};
        //    //matrix = exchangeYZ * matrix * exchangeYZ;// YZ轴对换

        //    go.transform.transform.FromMatrix(matrix);

        //    if (p_parent!=null && p_parent.parent==null)
        //    {
        //        go.transform.position = new Vector3(go.transform.position.x, go.transform.position.z, -go.transform.position.y);
        //    }
        //    foreach (var item in p_wrapper.Children)
        //    {
        //        GameObject itemChild = item.ToGameObject1(go.transform, p_directory);
        //    }

        //    return go;
        //}

    }
}
