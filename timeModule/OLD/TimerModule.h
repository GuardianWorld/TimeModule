/*#include "TimeSystem.hpp"
#include "AlarmClock.h"
#include "StopWatch.h"
#include "TimeFormat.h"
#include <vector>
#include <thread>

class TimerSystem {
private:
  //Timer System parts
  TimeSystem& timeSystemReference;
  int currentHour;
  int currentMinute;
  int alarmVectorSize;
  std::vector<std::pair<AlarmClock, bool>> alarms;
  StopWatch stopWatch;
  //Thread
  std::thread TimerThread;
  bool isRunning;
  
  std::string alarmOrWatchMessage;
  

public:

  TimerSystem(TimeSystem& timeSystem, std::string alarmOrWatchMessage) : timeSystemReference(timeSystem) {
    this->alarmOrWatchMessage = alarmOrWatchMessage;
    alarmVectorSize = 0;
    TimerThread = std::thread([this]() {
      while (isRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        executeSystem();
      }
    });
  }

  ~TimerSystem() {
      isRunning = false;
      TimerThread.join();
  }

  void executeSystem();
  void checkAlarms();

};
*/