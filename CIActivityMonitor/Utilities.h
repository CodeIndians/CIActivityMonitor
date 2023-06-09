#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip> // For setfill and setw
#include <string>
#include <sstream>

class Utilities
{
public:
	static std::string getCurrentDay() {
        // Get the current time
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // Convert the current time to the local time
        std::tm localTime;
        localtime_s(&localTime, &currentTime);

        // Format the day, month, and year
        int day = localTime.tm_mday;
        int month = localTime.tm_mon + 1;  // Months are 0-based, so add 1
        int year = localTime.tm_year + 1900;  // Years since 1900

        // Build the string with the formatted date
        std::stringstream oss;
        oss << std::setfill('0') << std::setw(2) << day << "-"
            << std::setfill('0') << std::setw(2) << month << "-"
            << year;

        return oss.str();
    }
};

