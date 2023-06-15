#include "ActivityCollector.h"
#include <algorithm>
#include "Utilities.h"
#include "json.hpp"

using json = nlohmann::json;

// initialize the static list
std::list<ActivityWindow> ActivityCollector::mActivityWindowsList;

// initialize the output json path
const std::string ActivityCollector::outputJsonPath = "C:/temp/activity.json";

/// <summary>
///  Utility function to write the collected data to file
/// </summary>
/// <param name="processName"> processName.exe </param>
/// <param name="elapsedTime"> elapsed time in seconds </param>
void ActivityCollector::WriteDatatoFile(std::string processName, double elapsedTime)
{
    // Open the file in append mode
    std::ofstream outputFile("C:/temp/activity.log", std::ios::app);
    if (outputFile.is_open())
    {
        //Put the data into the file 
        outputFile << "Process Name: " << processName << ", Time: " << elapsedTime << " seconds" << std::endl;

        // Close the file
        outputFile.close();
    }
    else
    {
        std::cerr << "Failed to open the log file for appending." << std::endl;
    }
}

/// <summary>
/// Collects the activity data into the activeWindows map
/// This will collect the process name and the time taken by the process
/// </summary>
void ActivityCollector::CollectActivityData()
{
    HWND activeWindowHandle = GetForegroundWindow();

    if (activeWindowHandle != nullptr)
    {
        // Update the active window's pid into the below varible
        DWORD processId;
        GetWindowThreadProcessId(activeWindowHandle, &processId);

        // Capture the process handle
        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);


        if (processHandle != nullptr)
        {
            wchar_t processName[MAX_PATH];

            //capture the process name into the processName variable
            if (GetModuleBaseName(processHandle, nullptr, processName, sizeof(processName) / sizeof(wchar_t)) != 0)
            {
                bool isFound = false;

                // convert processName from widechar to string
                auto processNameString = Utilities::convertWcharArraytoString(processName);

                // search for the process name in the captured activity window list
                // and update the Activity Window data
                for (auto& activeWindow : mActivityWindowsList)
                {
                    // identify if the activity window is already present and also check if the entry is from the current day
                    if (activeWindow.mProcessName == processNameString && Utilities::getCurrentDay() == activeWindow.sessionId)
                    {
                        isFound = true;

                        double elapsedTime = 0;

                        // capture the current time
                        auto curTime = std::chrono::system_clock::now();

                        // window is already active
                        if (activeWindow.isActive == true)
                        {
                            // update the 
                            elapsedTime = std::chrono::duration<double>(curTime - activeWindow.lastAccesedTime).count();
                        }
                        else
                        {
                            // switched to this window 
                            elapsedTime = 1;

                            //set the active state of the window
                            activeWindow.isActive = true;

                        }
                            
                        activeWindow.lastAccesedTime = curTime;

                        // add the calculate elapsedTime to the duration
                        activeWindow.totalDuration += elapsedTime;

                            
                    }
                    else
                    {
                        //reset the active state for all other windows
                        activeWindow.isActive = false; 
                    }

                }

                // no process entry in the list, Add it to the list
                if (!isFound)
                {
                    // a new entry gets added for the new window
                    mActivityWindowsList.emplace_back(processNameString);
                }
                
                // update the json 
                generateActivityWindowJson(mActivityWindowsList, outputJsonPath);

            }

            CloseHandle(processHandle);
        }
    }
    else
    {
        std::cerr << "No foreground window available." << std::endl;
    }
}

void ActivityCollector::generateActivityWindowJson(std::list<ActivityWindow>& activityWindows, const std::string& outputFile)
{
    json jsonData;

    for (const auto& activityWindow : activityWindows)
    {
        json activity;
        activity["ProcessName"] = activityWindow.mProcessName;
        activity["SessionId"] = activityWindow.sessionId;
        activity["firstAccesedTime"] = std::chrono::system_clock::to_time_t(activityWindow.firstAccesedTime);
        activity["lastAccesedTime"] = std::chrono::system_clock::to_time_t(activityWindow.lastAccesedTime);
        activity["totalDuration"] = activityWindow.totalDuration;
        activity["isActive"] = activityWindow.isActive;
        // ... other members

        jsonData.push_back(activity);
    }

    std::ofstream output(outputFile);
    if (output)
    {
        output << jsonData.dump(4);  // Indent with 4 spaces
    }
    else
    {
        std::cout << "Error opening output file: " << outputFile << std::endl;
    }
}
