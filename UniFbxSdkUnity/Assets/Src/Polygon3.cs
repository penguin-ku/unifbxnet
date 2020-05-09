using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace UniFbxSdkNet
{
    public class Polygon3
    {
        #region private members

        private int m_materialID;
        private Vertex3[] m_vertices;

        #endregion

        #region public properties

        /// <summary>
        /// get material id
        /// </summary>
        public int MaterialID
        {
            get
            {
                return m_materialID;
            }
            set
            {
                m_materialID = value;
            }
        }

        /// <summary>
        /// get vertices
        /// </summary>
        public Vertex3[] Vertices
        {
            get
            {
                return m_vertices.ToArray();
            }
        }

        #endregion

        #region constructors

        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="p_vertices">顶点集</param>
        /// <param name="p_objID">物体ID</param>
        /// <param name="p_materialID">材质ID</param>
        /// <remarks>参数顶点集，三个顶点顺序，右手螺旋决定法线方向</remarks>
        public Polygon3(Vertex3[] p_vertices, int p_materialID)
        {
            m_materialID = p_materialID;
            m_vertices = p_vertices;
        }

        #endregion

        #region public static functions

        /// <summary>
        /// generate mesh
        /// </summary>
        /// <param name="p_polygons">多边形集</param>
        /// <returns>网格</returns>
        public static Mesh GenerateMesh(List<Polygon3> p_polygons)
        {
            // 参数检查
            if (p_polygons == null || p_polygons.Count() == 0)
            {
                return null;
            }


            if (p_polygons.Any(p => p.MaterialID == -1))
            {
                for (int i = 0; i < p_polygons.Count; i++)
                {
                    p_polygons[i].MaterialID = p_polygons[i].MaterialID + 1;
                }
            }
            int materialsCount = p_polygons.Max(p => p.MaterialID) + 1;
            List<Vector3> vertices = new List<Vector3>();                                                                                   // 顶点
            List<Vector2> uvs = new List<Vector2>();                                                                                        // UV坐标
            List<Vector3> normals = new List<Vector3>();
            List<Color> colors = new List<Color>();
            List<int>[] submeshes = new List<int>[materialsCount];                                                                          // 子网格
            int subMeshCount = 0;                                                                                                           // 子网格数量

            foreach (var polygon in p_polygons)
            {
                Func<Vertex3, int> funVertex2Int = a =>
                {
                    vertices.Add(a.Position);                                                                                               // 添加顶点
                    uvs.Add(a.UV);                                                                                                          // 添加UV坐标
                    normals.Add(a.Normal);
                    colors.Add(a.Color);
                    return vertices.Count - 1;
                };

                int[] localArray = Enumerable.Select<Vertex3, int>(polygon.Vertices, funVertex2Int).ToArray();
                for (int i = 2; i < localArray.Length; i++)
                {
                    if (submeshes[polygon.MaterialID] == null)
                    {
                        submeshes[polygon.MaterialID] = new List<int>(100);
                        subMeshCount++;                                                                                                     // 子网格计数
                    }
                    submeshes[polygon.MaterialID].Add(localArray[0]);
                    submeshes[polygon.MaterialID].Add(localArray[i - 1]);
                    submeshes[polygon.MaterialID].Add(localArray[i]);
                }
            }

            Mesh sharedMesh = new Mesh();
            sharedMesh.indexFormat = vertices.Count < 65535 ? UnityEngine.Rendering.IndexFormat.UInt16 : UnityEngine.Rendering.IndexFormat.UInt32; // 支持65535
            sharedMesh.vertices = vertices.ToArray();
            sharedMesh.normals = normals.ToArray();
            //sharedMesh.colors = colors.ToArray();
            sharedMesh.subMeshCount = subMeshCount;
            int submeshIndex = 0;                                                                                                           // 子网格索引
            for (int i = 0; i < submeshes.Length; i++)
            {
                List<int> subMeshTriangles = submeshes[i];
                if ((subMeshTriangles != null) && (subMeshTriangles.Count > 0))
                {
                    sharedMesh.SetTriangles(subMeshTriangles.ToArray(), submeshIndex);                                                      // 设置子网格
                    submeshIndex++;
                }
            }
            sharedMesh.uv = uvs.ToArray();
            //sharedMesh.RecalculateNormals();                                                                                                // 重计算法线
            sharedMesh.RecalculateBounds();                                                                                                 // 重计算边界

            return sharedMesh;
        }

        /// <summary>
        /// generate GameObject
        /// </summary>
        /// <param name="p_polygos">多边形集</param>
        /// <param name="p_material">材质集</param>
        /// <returns></returns>
        public static GameObject GenerateObject(IEnumerable<Polygon3> p_polygos, IEnumerable<Material> p_material, bool p_isAddColider = true)
        {
            List<int> materialids = new List<int>();
            foreach (var item in p_polygos)
            {
                materialids.Add(item.MaterialID);
            }
            materialids = materialids.Distinct().ToList();
            materialids.Sort();

            GameObject gObject = new GameObject();
            MeshFilter meshfilter = gObject.AddComponent<MeshFilter>();
            meshfilter.sharedMesh = Polygon3.GenerateMesh(p_polygos.ToList());
            MeshRenderer renderer = gObject.AddComponent<MeshRenderer>();

            if (materialids.Contains(-1))// 存在无材质
            {
                List<Material> materials = new List<Material>()
                {
                    new Material(Shader.Find("Standard"))
                };
                materials.AddRange(p_material);
                renderer.materials = materialids.Select(p => materials[p + 1]).ToArray();
            }
            else
            {
                List<Material> materials = p_material.ToList();
                renderer.materials = materialids.Select(p => materials[p]).ToArray();
            }


            if (p_isAddColider)                                                                                             // 碰撞器
            {
                MeshCollider meshCollider = gObject.AddComponent<MeshCollider>();
                meshCollider.sharedMesh = meshfilter.sharedMesh;
            }

            return gObject;
        }

        #endregion
    }
}
