/*
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

        // 行名称自动前缀
        private static string rowPreName = "时间点_";

        // 列名称自动前缀
        private static string colPreName = "等级_";

        // 保存路径
        private static string path;

        public static void Error(string info)
        {
            string date = DateTime.Now.Year.ToString()+"年"+DateTime.Now.Month.ToString()+"月"+DateTime.Now.Day.ToString()+"日"+
                DateTime.Now.Hour.ToString()+"时"+DateTime.Now.Minute.ToString()+"分"+DateTime.Now.Second.ToString()+"秒"+DateTime.Now.Millisecond.ToString()+"毫秒";
          
       
            WriteValue(date, "Error", info);

            xmlDoc.Save(path);
        }
        public static void Warning(string info)
        {
            string date = DateTime.Now.Year.ToString() + "年" + DateTime.Now.Month.ToString() + "月" + DateTime.Now.Day.ToString() + "日" +
                 DateTime.Now.Hour.ToString() + "时" + DateTime.Now.Minute.ToString() + "分" + DateTime.Now.Second.ToString() + "秒" + DateTime.Now.Millisecond.ToString() + "毫秒";
            WriteValue(date, "Warning", info);
            xmlDoc.Save(path);
        }

        public static void Debug(string info)
        {
            string date = DateTime.Now.Year.ToString() + "年" + DateTime.Now.Month.ToString() + "月" + DateTime.Now.Day.ToString() + "日" +
                 DateTime.Now.Hour.ToString() + "时" + DateTime.Now.Minute.ToString() + "分" + DateTime.Now.Second.ToString() + "秒" + DateTime.Now.Millisecond.ToString() + "毫秒";
            WriteValue(date, "Debug", info);
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

        #region 写入值
        /// <summary>
        /// 在指定行列位置修改值，如果位置不存在，则添加，在此之前应该先创建或载入xml，否则失败
        /// </summary>
        /// <param name="rowKeyName">行首关键字，不存在则添加</param>
        /// <param name="colKeyName">列首关键字，不存在则添加</param>
        /// <param name="value"></param>
        private static void WriteValue(string rowKey, string colKey, string value)
        {
            rowKey = rowPreName + rowKey;

            colKey = colPreName + colKey;

            XmlElement newRow = xmlDoc.CreateElement(rowKey);
                    
            XmlElement newCol = xmlDoc.CreateElement(colKey);
          
            XmlElement val = xmlDoc.CreateElement("Info");
       
            val.InnerText = value;
        
            newCol.AppendChild(val);
            
            newRow.AppendChild(newCol);
                    
            root.AppendChild(newRow);
   
        }
        #endregion

        

    }
}
