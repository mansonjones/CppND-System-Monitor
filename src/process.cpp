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
pid_(pid),
user_(LinuxParser::User(pid)),
command_(LinuxParser::Command(pid)),
cpuUtilization_(0.432),
ram_(LinuxParser::Ram(pid_)),
uptime_(LinuxParser::UpTime(pid_))
  {
    setCachedActiveJiffies(1);
    setCachedIdleJiffies(1);
     
     // setCachedActiveJiffies(LinuxParser::ActiveJiffies(pid));
     // setCachedIdleJiffies(LinuxParser::IdleJiffies());
     
 }

int Process::Pid() const { return pid_; }

float Process::CpuUtilization() const {
    return 9.8765;
    // return CalculateUtilization<Process>(*this);
}

string Process::Command() const {
    return command_;  
}

string Process::Ram() const {  
    return ram_; 
}

string Process::User() const {
    return user_;
}

long int Process::UpTime() const { 
    return uptime_; 
}


void Process::update() {
    CpuUtilization();
    Command();
    Ram();
    User();
    UpTime();
}

long Process::ActiveJiffies() const {
    return LinuxParser::ActiveJiffies(pid_);
}

bool Process::operator<(Process const& a) const { 
    

    if ( std::stol(Ram()) > std::stol(a.Ram()) ) {
        return true;
    }
    if ( CpuUtilization() < a.CpuUtilization()) {
        return true;
    }
    
    return false; 
}

bool Process::operator>(Process const& a) const { 
    

    if ( std::stol(Ram()) > std::stol(a.Ram()) ) {
        return true;
    }
    if ( CpuUtilization() > a.CpuUtilization()) {
        return true;
    }
    
    return false; 
}

