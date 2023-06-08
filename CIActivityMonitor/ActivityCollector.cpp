#include "ActivityCollector.h"

std::unordered_map<HWND, std::chrono::steady_clock::time_point> ActivityCollector::activeWindows;

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
    HWND activeWindow = GetForegroundWindow();

    if (activeWindow != nullptr)
    {
        DWORD processId;
        GetWindowThreadProcessId(activeWindow, &processId);

        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
        if (processHandle != nullptr)
        {
            wchar_t processName[MAX_PATH];
            if (GetModuleBaseName(processHandle, nullptr, processName, sizeof(processName) / sizeof(wchar_t)) != 0)
            {
                if (activeWindows.find(activeWindow) == activeWindows.end())
                {
                    activeWindows[activeWindow] = std::chrono::steady_clock::now();
                }
                else
                {
                    std::chrono::steady_clock::time_point previousTime = activeWindows[activeWindow];
                    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
                    double elapsedTime = std::chrono::duration<double>(currentTime - previousTime).count();
                    activeWindows[activeWindow] = currentTime;

                    std::wstring wide_str_processName(processName);
                    // Append the process name to the file
                    std::string processNamestr(wide_str_processName.begin(), wide_str_processName.end());

                    // TODO: Write data to file. To be replaced with a DB.
                    WriteDatatoFile(processNamestr, elapsedTime);

                }
            }

            CloseHandle(processHandle);
        }
    }
    else
    {
        std::cerr << "No foreground window available." << std::endl;
    }
}
