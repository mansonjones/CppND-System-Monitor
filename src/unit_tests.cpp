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
  cout << " MemoryUtilization " << system.MemoryUtilization() << endl;
  cout << " UpTime() " << system.UpTime() << endl;
  cout << " TotalProcesses " << system.TotalProcesses() << endl;
  cout << " RunningProcesses " << system.RunningProcesses() << endl;
  cout << " Kernel() " << system.Kernel() << endl;
  cout << " OperatingSystem() " << system.OperatingSystem() << endl;
  cout << " process ids" <<endl;
  std::vector<Process> processes = system.Processes();
  cout << " cpu utilization" << system.Cpu().Utilization() << endl;
}

void UnitTests::testProcess(int pid) {
  Process process(pid);
  cout << "Process Tests" << endl;
  cout << "Pid() " << process.Pid() << endl;
  cout << "Ram() " << process.Ram() << endl;
  cout << "Command() " << process.Command() << endl;
  cout << "User() " << process.User() << endl;
  cout << "UpTime() " << process.UpTime() << endl;
}

void UnitTests::testJiffies(int pid) {
  cout << "LinuxParser::Jiffies() " << LinuxParser::Jiffies() << endl;
  cout << "LinuxParser::ActiveJiffies(pid) " << LinuxParser::ActiveJiffies(pid) << endl;
  cout << "LinuxParser::ActiveJiffies() " << LinuxParser::ActiveJiffies() << endl;
  cout << "LinuxParser::IdleJiffies() " << LinuxParser::IdleJiffies() << endl;

}
