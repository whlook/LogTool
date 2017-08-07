/*
    wuhui
*/
#pragma once 
#ifndef LOGTOOL_HPP_
#define LOGTOOL_HPP_

#include <iostream>
#include <ctime>
#include <Windows.h>
#include <string>
#include "tinyxml2.h"

namespace LogTool
{
	
	class Logger
	{
	public:
		/*
			init
		*/
		explicit Logger(std::string filePath)
		{
			path = filePath;

			root = xmlDoc.NewElement("logger");
			xmlDoc.InsertFirstChild(root);
			
			xmlDoc.SaveFile(filePath.c_str());
		}

		/*
			Error level
		*/
		void Error(std::string info)
		{
			std::string nowTime = getTime();
			writeValue("Error_"+nowTime, info);
			xmlDoc.SaveFile(path.c_str());
		}

		/*
			Warning level
		*/
		void Warning(std::string info)
		{
			std::string nowTime = getTime();
			writeValue("Warning_"+nowTime, info);
			xmlDoc.SaveFile(path.c_str());
		}

		/*
			Debug level
		*/
		void Debug(std::string info)
		{
			std::string nowTime = getTime();
			writeValue("Debug_"+nowTime, info);
			xmlDoc.SaveFile(path.c_str());
		}
	private:
		/*
			获得系统时间，精度 秒
		*/
		std::string getTime()
		{
			std::string timeNow;
			std::string temp;

			t = time(NULL);
			local = localtime(&t);

			temp = std::to_string(local->tm_year);
			timeNow += temp + "年";
			temp = std::to_string(local->tm_mon);
			timeNow += temp + "月";
			temp = std::to_string(local->tm_mday);
			timeNow += temp + "日";
			temp = std::to_string(local->tm_hour);
			timeNow += temp + "时";
			temp = std::to_string(local->tm_min);
			timeNow += temp + "分";
			temp = std::to_string(local->tm_sec);
			timeNow += temp + "秒";

			return timeNow;
			
		}
		/*
			写值
		*/
		void writeValue(std::string key, std::string value)
		{
	
			pElement = xmlDoc.NewElement(key.c_str());

			pElement->SetText(value.c_str());
	
			root->InsertEndChild(pElement);

		}

	private:
		tinyxml2::XMLDocument xmlDoc;
		tinyxml2::XMLNode * root = nullptr;
		tinyxml2::XMLElement * pElement = nullptr;

		std::string path;

		time_t t;
		struct tm *local;
		
	};


} // end LogTool
#endif //LOGTOOL_HPP_