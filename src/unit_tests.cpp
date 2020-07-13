#include "unit_tests.h"
#include "system.h"
#include "linux_parser.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

void UnitTests::testSystem() {
  System system;
  cout << "System Tests" << std::endl;
  cout << " MemoryUtilization " << system.MemoryUtilization() << std::endl;
  cout << " UpTime() " << system.UpTime() << std::endl;
  cout << " TotalProcesses " << system.TotalProcesses() << std::endl;
  cout << " RunningProcesses " << system.RunningProcesses() << std::endl;
  cout << " Kernel() " << system.Kernel() << std::endl;
  cout << " OperatingSystem() " << system.OperatingSystem() << std::endl;
  cout << " process ids" << std::endl;
  std::vector<Process> processes = system.Processes();
  std::cout << " cpu utilization" << system.Cpu().Utilization() << std::endl;
}

void UnitTests::testProcess(int pid) {
  Process process(pid);
  std::cout << "Process Tests" << std::endl;
  std::cout << "Pid() " << process.Pid() << std::endl;
  std::cout << "Ram() " << process.Ram() << std::endl;
  std::cout << "Command() " << process.Command() << std::endl;
  std::cout << "User() " << process.User() << std::endl;
  std::cout << "UpTime() " << process.UpTime() << std::endl;
}

void UnitTests::testJiffies(int pid) {
  std::cout << "LinuxParser::Jiffies() " << LinuxParser::Jiffies() << std::endl;
  std::cout << "LinuxParser::ActiveJiffies(pid) " << LinuxParser::ActiveJiffies(pid) << std::endl;
  std::cout << "LinuxParser::ActiveJiffies() " << LinuxParser::ActiveJiffies() << std::endl;
  std::cout << "LinuxParser::IdleJiffies() " << LinuxParser::IdleJiffies() << std::endl;

}
