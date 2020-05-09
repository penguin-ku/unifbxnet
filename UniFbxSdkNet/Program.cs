using UniFbxSdkNet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CFbxSdkNet
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(string.Format("{0} begin  {1}", @"F:\penguin_ku.personal\unifbxnet\testmodel\test202.FBX", DateTime.Now.ToString("HH:mm:ss ffff")));

            UniGameObjectWrapper wrapper = UniFbxSdkWrapper.Load(@"F:\penguin_ku.personal\unifbxnet\testmodel\test101.FBX");

            Console.WriteLine(string.Format("{0} end  {1}", @"F:\penguin_ku.personal\unifbxnet\testmodel\test202.FBX", DateTime.Now.ToString("HH:mm:ss ffff")));

            Console.ReadKey();

            //int[] mm = new int[10];
            //UniFbxSdkRef.GetIntArray(10, mm);
        }
    }
}
