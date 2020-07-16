#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include <iostream> // remove after debugging is done

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"



using std::set;
using std::size_t;
using std::string;
using std::vector;


System::System() : cpu_(Processor()) {}

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
    
    // Create a set of pids
    set<int> existing_pids;
    for (Process const& process: processes_) {
        existing_pids.insert(process.Pid());
    }

    // If the process is not already in the list of processes,
    // then add it.  Note that emplace_back avoids having 
    // to call the Process constructor explicitly
    for (int pid : pids) {
        if (existing_pids.find(pid) == existing_pids.end()) {
            processes_.emplace_back(pid);
          // processes_.push_back(Process(pid));
        }
    }
    
    // Update all processes
    
    for (auto& process: processes_) {
        process.update();
    }
    
    std::sort(processes_.begin(), processes_.end(), std::greater<Process>());
    return processes_;
    /* Here is his code from the demo
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
        process.CpuUtilization(LinuxParser::ActiveJiffies(process.Pid()))
        LinuxParser::Jiffies());
    }

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