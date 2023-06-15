#pragma once
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <fstream>
#include <chrono>
#include <locale>
#include <list>
#include "ActivityWindow.h"

class ActivityCollector
{
private:
	static std::list<ActivityWindow> mActivityWindowsList;
	static void WriteDatatoFile(std::string processName, double elapsedTime);
	static const std::string outputJsonPath;
public:
	static void CollectActivityData();
	static void generateActivityWindowJson(std::list<ActivityWindow>& activityWindows, const std::string& outputFile);
};


