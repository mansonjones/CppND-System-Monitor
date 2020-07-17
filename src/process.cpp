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
ram_(LinuxParser::Ram(pid)),
uptime_(LinuxParser::UpTime(pid))
  {
    setCachedActiveJiffies(0);
    setCachedIdleJiffies(0);
     
 }

int Process::Pid() const { return pid_; }

float Process::CpuUtilization() const {
   return cpuUtilization_;
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
    user_ = LinuxParser::User(pid_);
    command_ = LinuxParser::Command(pid_);

    long upTime = LinuxParser::UpTime() * sysconf(_SC_CLK_TCK);
    long processTime = LinuxParser::ActiveJiffies(pid_);
    cpuUtilization_ = static_cast<float>(processTime)/static_cast<float>(upTime); 
 
    ram_ = LinuxParser::Ram(pid_);
    uptime_ = LinuxParser::UpTime(pid_);

}

long Process::ActiveJiffies() const {
    return LinuxParser::ActiveJiffies(pid_);
}

bool Process::operator<(Process const& a) const { 
    if ( std::stol(Ram()) > std::stol(a.Ram()) ) {
        return true;
    }

    return false; 
}

bool Process::operator>(Process const& a) const { 

    if ( std::stol(Ram()) > std::stol(a.Ram()) ) {
        return true;
    }
    
    return false; 
}

