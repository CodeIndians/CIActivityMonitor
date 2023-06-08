// TestActivity.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ActivityCollector.h"

std::unordered_map<HWND, std::chrono::steady_clock::time_point> activeWindows;

int main()
{
    // run the main loop at a fixed interval of 2 seconds for now 
    while (true)
    {
        ActivityCollector::CollectActivityData();
        Sleep(2000);
    }
}
