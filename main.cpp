/*
#include "Headers/defines.h"
#include "Headers/languageSystem.h"
#include "Headers/LogModule.h"
#include "Headers/systemCommands.h"
*/

#include <iostream>
#include <string>
#include "timeModule/TimeImport.hpp"

#include "printModule/PrintThread.hpp"

int main()
{
	TimeThread& clock = TimeThread::getInstance();
    PrintThread& printer = PrintThread::getInstance();

	//std::this_thread::sleep_for(std::chrono::milliseconds(10));

	printer << "Hello World!";
	printer << "Testing";

	int x = 0;
	//std::cin >> x;

	// Ensure the printing thread finishes before exiting

	return 0;
}