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
		*/
		explicit Logger(std::string filePath)
		{
			path = filePath;
			colPreName = "等级";
			rowPreName = "时间点";
			root = xmlDoc.NewElement("logger");
			xmlDoc.InsertFirstChild(root);
			
			xmlDoc.SaveFile(filePath.c_str());
		}

		/*
		*/
		void Error(std::string info)
		{
			std::string nowTime = getTime();
			writeValue(nowTime, "Error", info);
			xmlDoc.SaveFile(path.c_str());
		}

		/*
		*/
		void Warning(std::string info)
		{
			std::string nowTime = getTime();
			writeValue(nowTime, "Warning", info);
			xmlDoc.SaveFile(path.c_str());
		}

		/*
		*/
		void Debug(std::string info)
		{
			std::string nowTime = getTime();
			writeValue(nowTime, "Debug", info);
			xmlDoc.SaveFile(path.c_str());
		}
	private:
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

		void writeValue(std::string rowKey, std::string colKey, std::string value)
		{
			rowKey = rowPreName + rowKey;
			colKey = colPreName + colKey;

			pElement = xmlDoc.NewElement(rowKey.c_str());
			pElement_sub = xmlDoc.NewElement(colKey.c_str());
			pElement_sub_ = xmlDoc.NewElement("info");

			pElement_sub_->SetText(value.c_str());
			pElement_sub->InsertFirstChild(pElement_sub_);
			pElement->InsertFirstChild(pElement_sub);

			root->InsertEndChild(pElement);

		}

	private:
		tinyxml2::XMLDocument xmlDoc;
		tinyxml2::XMLNode * root = nullptr;
		tinyxml2::XMLElement * pElement = nullptr;
		tinyxml2::XMLElement * pElement_sub = nullptr;
		tinyxml2::XMLElement * pElement_sub_ = nullptr;

		std::string rowPreName, colPreName;

		std::string path;

		time_t t;
		struct tm *local;
		
	};


}
#endif //LOGTOOL_HPP_