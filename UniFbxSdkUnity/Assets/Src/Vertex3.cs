using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace UniFbxSdkNet
{
    public class Vertex3
    {
        #region private members

        private Vector3 m_position;
        private Vector2 m_uv;
        private Vector3 m_normal;
        private Color m_color;

        #endregion

        #region public properties

        /// <summary>
        /// get position
        /// </summary>
        public Vector3 Position
        {
            get
            {
                return m_position;
            }
        }

        ///// <summary>
        ///// get uv
        ///// </summary>
        public Vector2 UV
        {
            get
            {
                return m_uv;
            }
        }

        /// <summary>
        /// get normal
        /// </summary>
        public Vector3 Normal
        {
            get
            {
                return m_normal;
            }
        }

        /// <summary>
        /// 获取颜色
        /// </summary>
        public Color Color
        {
            get
            {
                return m_color;
            }
        }


        #endregion

        #region constructors

        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="p_position">三维坐标</param>
        /// <param name="p_uv">UV坐标</param>
        public Vertex3(Vector3 p_position, Vector2 p_uv, Vector3 p_normal, Color p_color)
        {
            m_position = p_position;
            m_uv = p_uv;
            m_normal = p_normal;
            m_color = p_color;
        }

        #endregion
    }
}
