#pragma once
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <locale>

class ActivityCollector
{
private:
	static std::unordered_map<HWND, std::chrono::steady_clock::time_point> activeWindows;
	static void WriteDatatoFile(std::string processName, double elapsedTime);
public:
	static void CollectActivityData();
};

