#include "ActivityWindow.h"
#include "Utilities.h"

ActivityWindow::ActivityWindow()
{
	// do the time fetching operation only once since it is expensive
	auto temp = std::chrono::system_clock::now();
	firstAccesedTime = temp;
	lastAccesedTime = temp;
	mProcessName = "DefaultProcess";
	totalDuration = 0;
	isActive = true;
	sessionId = Utilities::getCurrentDay();
}

ActivityWindow::ActivityWindow(std::string processName)
{
	// do the time fetching operation only once since it is expensive
	auto temp = std::chrono::system_clock::now();
	firstAccesedTime = temp;
	lastAccesedTime = temp;
	mProcessName = processName;
	totalDuration = 0;
	isActive = true;
	sessionId = Utilities::getCurrentDay();
}
