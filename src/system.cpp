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



System::System() : cpu_(Processor()) {}

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    
    vector<int> pids{LinuxParser::Pids()};
    // Update the current list of processes.
    // Delete any processes that are in the list but are 
    // not in /proc/[pid]
    // Add any new processes. 
    // It might be better to just clear the list and start over
    processes_.clear();
    for (int pid : pids) {
        Process process = Process(pid);
        processes_.push_back(process);
    }
    // Update CPU utilization
    for (auto& process: processes_) {
        process.CpuUtilization();
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_;
    /*
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

    std::sort(processes_.begin(), processes_.end(), std::g
    */
}

std::string System::Kernel() const { 
    return LinuxParser::Kernel(); 
}

float System::MemoryUtilization() const { 
    return LinuxParser::MemoryUtilization(); 
}

std::string System::OperatingSystem() const { 
    return LinuxParser::OperatingSystem(); 
}

int System::RunningProcesses() const { 
    return LinuxParser::RunningProcesses(); 
}

int System::TotalProcesses() const { 
    return LinuxParser::TotalProcesses(); 
}

long int System::UpTime() const { 
    return LinuxParser::UpTime(); 
}