using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace UniFbxSdkNet
{
    public class UniGameObjectWrapper
    {
        public string Name;
        public UniTransform Transform;
        public UniGeoTransform GeometryTransform;
        public UniMaterial[] Materials;// 材质通道不超过24
        public UniPolygon[] Polygons;
        public UniGameObjectWrapper[] Children;
    }


    public static class UniFbxSdkWrapper
    {
        public static string ToString(this byte[] p_data, int p_length)
        {
            string str = System.Text.Encoding.GetEncoding("GBK").GetString(p_data, 0, p_length);
            return str;
        }
        public static byte[] ToBytes(this string p_data)
        {
            byte[] bytes = System.Text.Encoding.GetEncoding("GBK").GetBytes(p_data);
            return bytes;
        }


        public static UniGameObjectWrapper Load(string p_path)
        {
            System.IO.FileInfo info = new System.IO.FileInfo(p_path);
            if (info.Exists)
            {

                FbxManagerRef fbxManagerRef = default(FbxManagerRef);
                FbxNodeRef fbxNodeRef = default(FbxNodeRef);
                byte[] byets = p_path.ToBytes();
                UniFbxSdkRef.Load(byets, ref fbxManagerRef, ref fbxNodeRef);

                Console.WriteLine(System.DateTime.Now.ToString());
                UniGameObjectWrapper gameObjectWrapper = ParseGameObject(fbxNodeRef, "root");

                UniFbxSdkRef.Destroy(fbxManagerRef);
                gameObjectWrapper.Name = info.Name;
                return gameObjectWrapper;

            }
            else
            {
                return new UniGameObjectWrapper()
                {
                    Transform = new UniTransform() { mm = new double[16] { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 } },
                    GeometryTransform = new UniGeoTransform() { mm = new double[16] { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 } },
                    Name = info.Name,
                    Children = new UniGameObjectWrapper[0],
                    Materials = new UniMaterial[0],
                    Polygons = new UniPolygon[0]
                };
            }
        }

        private static UniGameObjectWrapper ParseGameObject(FbxNodeRef fbxNodeRef, string path)
        {
            UniGameObjectWrapper gameObjectWrapper = new UniGameObjectWrapper();

            Console.WriteLine(string.Format("{0} begin  {1}", path, DateTime.Now.ToString("HH:mm:ss ffff")));

            UniGameObject uniGameObject = default(UniGameObject);
            UniFbxSdkRef.GetGameObject(fbxNodeRef, ref uniGameObject);
            gameObjectWrapper.Name = uniGameObject.mName.ToString(uniGameObject.iNameLength);
            gameObjectWrapper.Transform = uniGameObject.mTransform;
            gameObjectWrapper.GeometryTransform = uniGameObject.mGeometryTransform;

            gameObjectWrapper.Materials = UniFbxSdkRef.GetMaterials(fbxNodeRef);
            gameObjectWrapper.Polygons = UniFbxSdkRef.GetPolygons(fbxNodeRef);
            FbxNodeRef[] childrenNodes = UniFbxSdkRef.GetChildrenNodes(fbxNodeRef);
            gameObjectWrapper.Children = new UniGameObjectWrapper[childrenNodes.Length];
            for (int i = 0; i < childrenNodes.Length; i++)
            {
                FbxNodeRef childRef = childrenNodes[i];
                string childPath = string.Format("{0}-{1}", path, i);
                gameObjectWrapper.Children[i] = ParseGameObject(childRef, childPath);
            }

            Console.WriteLine(string.Format("{0} end  {1}", path, DateTime.Now.ToString("HH:mm:ss ffff")));

            return gameObjectWrapper;
        }
    }

}
