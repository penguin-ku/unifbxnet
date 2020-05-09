using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.TaskExtension;

namespace UniFbxSdkNet
{
    public class UniFbxSdkDemo : MonoBehaviour
    {
        //public string Path;
        //public string MaterialPath;

        string erro = null;
        // Update is called once per frame
        void Update()
        {
            if (Input.GetKeyDown(KeyCode.A))
            {
                Task.Run(() =>
                {
                    try
                    {
                        Debug.Log(System.DateTime.Now.ToString());
                        UniGameObjectWrapper gameobjectData = UniFbxSdkWrapper.Load(@"F:\penguin_ku.personal\unifbxnet\testmodel\CZ-5.FBX");
                        Debug.Log(System.DateTime.Now.ToString());
                        return gameobjectData;
                    }
                    catch (Exception ex)
                    {
                        throw ex;
                    }
                }).ContinueToForeground(t =>
                {
                    if (t.IsFaulted)
                    {
                        Debug.Log(t.Exception);
                    }
                    else
                    {
                        GameObject go = t.Result.ToGameObject(null, @"F:\penguin_ku.personal\unifbxnet\testmodel");
                        Debug.Log(System.DateTime.Now.ToString());
                    }
                });
            }
            if (Input.GetKeyDown(KeyCode.B))
            {
                Task.Run(() =>
                {
                    Debug.Log(System.DateTime.Now.ToString());
                    UniGameObjectWrapper gameobjectData = UniFbxSdkWrapper.Load(@"F:\penguin_ku.personal\unifbxnet\testmodel\测试-5\CZ-5www.FBX");
                    Debug.Log(System.DateTime.Now.ToString());
                    return gameobjectData;
                }).ContinueToForeground(t =>
                {
                    if (t.IsFaulted)
                    {
                        Debug.Log(t.Exception);
                    }
                    else
                    {
                        GameObject go = t.Result.ToGameObject(null, @"F:\penguin_ku.personal\unifbxnet\testmodel");
                        Debug.Log(System.DateTime.Now.ToString());
                    }
                });
            }
        }

        private void OnGUI()
        {
            if (!string.IsNullOrEmpty(erro))
            {
                GUI.TextArea(new Rect(10, 10, 300, 400), erro);
            }
        }
    }
}
