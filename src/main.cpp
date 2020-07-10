#include "ncurses_display.h"
#include "system.h"

#include <iostream>

void testSystem() {
  System system;
  std::cout << "System Tests" << std::endl;
  std::cout << " MemoryUtilization " << system.MemoryUtilization() << std::endl;
  std::cout << " UpTime() " << system.UpTime() << std::endl;
  std::cout << " TotalProcesses " << system.TotalProcesses() << std::endl;
  std::cout << " RunningProcesses " << system.RunningProcesses() << std::endl;
  std::cout << " Kernel() " << system.Kernel() << std::endl;
  std::cout << " OperatingSystem() " << system.OperatingSystem() << std::endl;
  std::cout << " process ids" << std::endl;
  std::vector<Process> processes = system.Processes();
  std::cout << " cpu utilization" << system.Cpu().Utilization() << std::endl;
}

void testProcess(int pid) {
  Process process(pid);
  std::cout << "Process Tests" << std::endl;
  std::cout << "Pid() " << process.Pid() << std::endl;
  std::cout << "Ram() " << process.Ram() << std::endl;
  std::cout << "Command() " << process.Command() << std::endl;
  std::cout << "User() " << process.User() << std::endl;
  std::cout << "UpTime() " << process.UpTime() << std::endl;
}

int main() {
  System system;
  testSystem();
  testProcess(1182);
  // NCursesDisplay::Display(system);
}