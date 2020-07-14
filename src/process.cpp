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

Process::Process(int pid) :
 pid_(pid) {
     setCachedActiveJiffies(LinuxParser::ActiveJiffies());
     setCachedIdleJiffies(LinuxParser::IdleJiffies());
 }

int Process::Pid() const { return pid_; }

float Process::CpuUtilization() const {
    return CalculateUtilization<Process>(*this);
}

string Process::Command() const { 
    return LinuxParserNew::Command(pid_); 
}

string Process::Ram() const { 
    return LinuxParserNew::Ram(pid_); 
}

string Process::User() const { 
    return LinuxParserNew::User(pid_); 
}

long int Process::UpTime() const { 
    return LinuxParserNew::UpTime(pid_); 
}

long Process::ActiveJiffies() const {
    return LinuxParserNew::ActiveJiffies(pid_);
}

bool Process::operator<(Process const& a) const { 
    
    if (Ram() < a.Ram()) {
        return true;
    }
    if ( CpuUtilization() < a.CpuUtilization()) {
        return true;
    }
    
    return false; 
}

