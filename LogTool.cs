﻿/*
作者：吴辉
*/
using System;
using System.IO;
using System.Xml;
using System.Linq;
using System.Text;
using System.Collections;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace LogTool
{
   public class logger
    {
        // 操作对象
        private static XmlDocument xmlDoc = null;

        // 根节点
        private static XmlElement root = null;

        // 保存路径
        private static string path;

        public static void Error(string info)
        {
            string date = DateTime.Now.Year.ToString()+"年"+DateTime.Now.Month.ToString()+"月"+DateTime.Now.Day.ToString()+"日"+
                DateTime.Now.Hour.ToString()+"时"+DateTime.Now.Minute.ToString()+"分"+DateTime.Now.Second.ToString()+"秒"+DateTime.Now.Millisecond.ToString()+"毫秒";

            XmlElement val = xmlDoc.CreateElement("Error_"+date);
       
            val.InnerText = info;

            root.AppendChild(val);

            xmlDoc.Save(path);
        }
        public static void Warning(string info)
        {
            string date = DateTime.Now.Year.ToString() + "年" + DateTime.Now.Month.ToString() + "月" + DateTime.Now.Day.ToString() + "日" +
                 DateTime.Now.Hour.ToString() + "时" + DateTime.Now.Minute.ToString() + "分" + DateTime.Now.Second.ToString() + "秒" + DateTime.Now.Millisecond.ToString() + "毫秒";
            
            XmlElement val = xmlDoc.CreateElement("Warning_"+date);
       
            val.InnerText = info;

            root.AppendChild(val);

            xmlDoc.Save(path);
        }

        public static void Debug(string info)
        {
            string date = DateTime.Now.Year.ToString() + "年" + DateTime.Now.Month.ToString() + "月" + DateTime.Now.Day.ToString() + "日" +
                 DateTime.Now.Hour.ToString() + "时" + DateTime.Now.Minute.ToString() + "分" + DateTime.Now.Second.ToString() + "秒" + DateTime.Now.Millisecond.ToString() + "毫秒";
            
            XmlElement val = xmlDoc.CreateElement("Debug_"+date);
       
            val.InnerText = info;

            root.AppendChild(val);

            xmlDoc.Save(path);
        }
 

        #region 创建日志
       
        public static bool SetLogFilePath(string filePath)
        {
            path = filePath;

            if (!File.Exists(filePath)) // 如果不存在该文件，则创建，并生成根节点
            {
                xmlDoc = new XmlDocument();

                root = xmlDoc.CreateElement("logger");

                xmlDoc.AppendChild(root);

                xmlDoc.Save(filePath);

                return true;
            }
            else
            {
                if (!LoadLogFile(filePath))
                {
                    return false;
                }
                return true;
            }
        }
        #endregion

        #region 载入日志
     
        private static bool LoadLogFile(string filePath)
        {
            if (!File.Exists(filePath)) // 如果不存在，则载入失败
            {
                return false;
            }
            else
            {
                
                if (xmlDoc == null)
                {
                    xmlDoc = new XmlDocument();

                    xmlDoc.Load(filePath);

                    root = (XmlElement)xmlDoc.SelectSingleNode("logger"); // 读取根节点

                    if (root == null)
                        return false;

                    return true;
                }
                else
                {
                    xmlDoc.Load(filePath);

                    root = (XmlElement)xmlDoc.SelectSingleNode("logger"); // 读取根节点

                    if (root == null)
                        return false;

                    return true;
                }
            }
        }
        #endregion

    }
}
