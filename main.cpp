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
	AlarmManager alarmManager(clock, printer);

	printer << "Hello World!\n \f";
	printer << "Testing\n";

	int x = 0;
	int hour = 0;
	int minute = 0;
	while(hour != -1){
		printer << "Enter an hour and minute to add an alarm (or -1 to exit): ";
		std::cin >> hour;
		if(hour == -1) break;
		std::cin >> minute;
		alarmManager.add_alarm(AlarmManager::build_alarm("Test", hour, minute));
		printer << "Alarm added! Now to wait!\n";
	}

	// Ensure the printing thread finishes before exiting

	return 0;
}