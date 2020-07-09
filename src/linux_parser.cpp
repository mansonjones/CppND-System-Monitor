#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string lineBuffer;
  string key, value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, lineBuffer)) {
      std::replace(lineBuffer.begin(), lineBuffer.end(), ' ', '_');
      std::replace(lineBuffer.begin(), lineBuffer.end(), '=', ' ');
      std::replace(lineBuffer.begin(), lineBuffer.end(), '"', ' ');
      std::istringstream linestream(lineBuffer);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string lineBuffer;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string lineBuffer;
  string key, value;
  float memTotal = 1.0;
  float memFree = 0.0;
  //float memAvailable = 0.0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal = atof(value.c_str());
        }
        if (key == "MemFree:") {
          memFree = atof(value.c_str());
        }
        /*
        if (key == "MemAvailable:") {
          memAvailable = atof(value.c_str());
        }
        */
      }
    }
  }

  return (memTotal - memFree) / memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime1, uptime2;
  string lineBuffer;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> uptime1 >> uptime2;
    return atol(uptime1.c_str());
  }
  return 0; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string key, userJiffies, niceJiffies, systemJiffies, idleJiffies;
  string lineBuffer;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> key >> userJiffies >> niceJiffies >> systemJiffies >> idleJiffies;
    if (key == "cpu") {
      return atol(userJiffies.c_str());
    }
  }
  return 0; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
string key, userJiffies, niceJiffies, systemJiffies, idleJiffies;
  // 1 pid
  // 2 comm
  // 3 state (R, S, D, Z, T, t, W, X, x, K, W, P)
  // 4 ppid
  // 5 pgrp
  // 6 session
  // 7 tty nc
  // 8 tpgid
  // 9 flags
  // 10 minflt
  // 11 cminflt
  // 12 majflt
  // 13 cmajflt
  // 14 utime - user time
  // 15 stime - time in kernel mode
  // 16 cutime - children user time
  
  string lineBuffer;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> key >> userJiffies >> niceJiffies >> systemJiffies >> idleJiffies;
    if (key == "cpu") {
      return atol(userJiffies.c_str());
    }
  }
  return 0;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string key, userJiffies, niceJiffies, systemJiffies, idleJiffies;
  string lineBuffer;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> key >> userJiffies >> niceJiffies >> systemJiffies >> idleJiffies;
    if (key == "cpu") {
      return atol(userJiffies.c_str());
    }
  }
  return 0; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string key, userJiffies, niceJiffies, systemJiffies, idleJiffies;
  string lineBuffer;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> key >> userJiffies >> niceJiffies >> systemJiffies >> idleJiffies;
    if (key == "cpu") {
      return atol(userJiffies.c_str());
    }
  }
  return 0; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> utilizations;
  utilizations.push_back("0.5");
  return utilizations;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key, value;
  string lineBuffer;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      linestream >> key >> value;
      if (key == "processes") {
        return stoi(value);
      }
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key, value;
  string lineBuffer;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      linestream >> key >> value;
      if (key == "procs_running") {
        return stoi(value);
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string command;
  string lineBuffer;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    return lineBuffer;
  }
  return string(); 
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string key, value;
  string lineBuffer;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          return value;
        }
      }
    }
  }
  return string(); 
}

// TODO: Read and return the user ID associated with a process
// 
string LinuxParser::Uid(int pid) { 
  string key, value;
  string lineBuffer;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return string(); 
}

// TODO: Read and return the user associated with a process
// 
string LinuxParser::User(int pid) 
{ 
  string token;
  std::ifstream filestream(kPasswordPath);
  string uid = Uid(pid);
  std::vector<string> tokens;
  const char delimiter = ':';
  if (filestream.is_open()) {
    while (std::getline(filestream, token, delimiter)) {
      tokens.push_back(token);
    }
    if (tokens[2] == uid) {
      return tokens[0];
    }
  }
  
  return string(); 
}

// TODO: Read and return the uptime of a process
// 
long LinuxParser::UpTime(int pid) { 
  string uptime1, uptime2;
  string lineBuffer;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> uptime1 >> uptime2;
    return stoi(uptime1);
  }
  return 0; 
}