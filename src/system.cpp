#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    /*
    vector<int> pids{LinuxParser::Pids()};

    // Create a set
    set<int> extant_pids;
    for (Process const& process:  processes_) {
        extant_pid.insert(process.Pid());
    }
    // Emplace all new processes
    for (int pid : pids) {
        if (extant_pids.find(pid) == extant_pids.end()) {
            processes_.emplace_back(pid);
        }
    }

    // Update CPU utiliztion
    for (auto& process : processes) {
        process.CpuUtilization(LinuxParser::ActiveJiffies(process))
        LinuxParser::Jiffies());
    }
    */
    Process process = Process(1);
    processes_.push_back(process);
    return processes_; 
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() const { 
    return LinuxParser::Kernel(); 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() const { 
    return LinuxParser::MemoryUtilization(); 
}

std::string System::OperatingSystem() const { 
    return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() const { 
    return LinuxParser::RunningProcesses(); 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() const { 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() const { 
    // call the format function
    return LinuxParser::UpTime(); 
}