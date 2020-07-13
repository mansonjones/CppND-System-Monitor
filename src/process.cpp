#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_{pid} {}

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    // This will need the pid_
    return 0; 
}

string Process::Command() const { 
    return LinuxParser::Command(pid_); 
}

string Process::Ram() const { 
    return LinuxParser::Ram(pid_); 
}

string Process::User() const { 
    return LinuxParser::User(pid_); 
}

long int Process::UpTime() const { 
    return LinuxParser::UpTime(pid_); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    
    if (Ram() < a.Ram()) {
        return true;
    }
    if ( CpuUtilization() < a.CpuUtilization()) {
        return true;
    }
    
    return false; 
}