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
			colPreName = "�ȼ�";
			rowPreName = "ʱ���";
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
			writeValue(nowTime, "Error", info);
			xmlDoc.SaveFile(path.c_str());
		}

		/*
			Warning level
		*/
		void Warning(std::string info)
		{
			std::string nowTime = getTime();
			writeValue(nowTime, "Warning", info);
			xmlDoc.SaveFile(path.c_str());
		}

		/*
			Debug level
		*/
		void Debug(std::string info)
		{
			std::string nowTime = getTime();
			writeValue(nowTime, "Debug", info);
			xmlDoc.SaveFile(path.c_str());
		}
	private:
		/*
			���ϵͳʱ�䣬���� ��
		*/
		std::string getTime()
		{
			std::string timeNow;
			std::string temp;

			t = time(NULL);
			local = localtime(&t);

			temp = std::to_string(local->tm_year);
			timeNow += temp + "��";
			temp = std::to_string(local->tm_mon);
			timeNow += temp + "��";
			temp = std::to_string(local->tm_mday);
			timeNow += temp + "��";
			temp = std::to_string(local->tm_hour);
			timeNow += temp + "ʱ";
			temp = std::to_string(local->tm_min);
			timeNow += temp + "��";
			temp = std::to_string(local->tm_sec);
			timeNow += temp + "��";

			return timeNow;
			
		}
		/*
			�������и�ʽдֵ
		*/
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


} // end LogTool
#endif //LOGTOOL_HPP_