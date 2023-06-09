// TestActivity.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ActivityCollector.h"

int main()
{
    // run the main loop at a fixed interval of 2 seconds for now 
    while (true)
    {
        ActivityCollector::CollectActivityData();
        Sleep(2000);
    }
}
