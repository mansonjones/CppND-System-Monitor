#include "ncurses_display.h"
#include "system.h"

#include <iostream>

void testSystem() {
  System system;
  std::cout << "System Tests" << std::endl;
  std::cout << system.MemoryUtilization() << std::endl;
  std::cout << system.UpTime() << std::endl;
  std::cout << system.TotalProcesses() << std::endl;
  std::cout << system.RunningProcesses() << std::endl;
  std::cout << system.Kernel() << std::endl;
  std::cout << system.OperatingSystem() << std::endl;
}

void testProcess(int pid) {
  Process process(pid);
  std::cout << "Process Tests" << std::endl;
  std::cout << process.Command() << std::endl;
  std::cout << process.Ram() << std::endl;
  std::cout << process.Pid() << std::endl;
  std::cout << process.User() << std::endl;
  std::cout << process.UpTime() << std::endl;
}

int main() {
  System system;
  testSystem();
  testProcess(3007);
  // NCursesDisplay::Display(system);
}