#pragma once
#include <iostream>
#include <chrono>

class ActivityWindow
{
public:
	std::string mProcessName; // process name 
	std::string sessionId;   // should be mapped to each day of the year ( 1 to 365/366 days)
	std::chrono::system_clock::time_point firstAccesedTime;
	std::chrono::system_clock::time_point lastAccesedTime;
	double totalDuration;
	bool isActive;
	explicit ActivityWindow(std::string processName);
};

