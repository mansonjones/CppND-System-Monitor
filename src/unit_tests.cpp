#include "unit_tests.h"
#include "system.h"
#include "linux_parser.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

void UnitTests::testSystem() {
  System system;
  cout << "*** System Tests ***" << std::endl;
  cout << " MemoryUtilization " << system.MemoryUtilization() << endl;
  cout << " UpTime() " << system.UpTime() << endl;
  cout << " TotalProcesses " << system.TotalProcesses() << endl;
  cout << " RunningProcesses " << system.RunningProcesses() << endl;
  cout << " Kernel() " << system.Kernel() << endl;
  cout << " OperatingSystem() " << system.OperatingSystem() << endl;

  std::vector<Process> processes = system.Processes();
  cout << " cpu utilization " << system.Cpu().Utilization() << endl;
  cout << endl;
}

void UnitTests::testProcess(int pid) {
  Process process(pid);
  cout << "*** Process Tests ***" << endl;
  cout << "Pid() " << process.Pid() << endl;
  cout << "Ram() " << process.Ram() << endl;
  cout << "Command() " << process.Command() << endl;
  cout << "User() " << process.User() << endl;
  cout << "UpTime() " << process.UpTime() << endl;
  cout << endl;
}

void UnitTests::testLinuxParser(int pid) {
  cout << "*** LinuxParser Tests ***" << endl;
  std::vector<int> pids = LinuxParser::Pids();
  cout << "LinuxParser::Pids()" << endl;
  cout << " number of pids " << pids.size() << std::endl;
  for (int pid: pids) {
    cout << pid << " ";
  }
  cout << endl;
  cout << "LinuxParser::Jiffies() " << LinuxParser::Jiffies() << endl;
  cout << "LinuxParser::ActiveJiffies(pid) " << LinuxParser::ActiveJiffies(pid) << endl;
  cout << "LinuxParser::ActiveJiffies() " << LinuxParser::ActiveJiffies() << endl;
  cout << "LinuxParser::IdleJiffies() " << LinuxParser::IdleJiffies() << endl;
  cout << endl;
}

void UnitTests::testProcessor() {
  cout << "*** Processor Tests ***" << endl;
  Processor processor;
  cout << "Utilization() " << processor.Utilization();
  cout << endl;
}
