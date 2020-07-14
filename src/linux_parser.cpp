#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <thread> // Needed for delay in CpuUtilization()
#include <chrono> // Needed for delay in CpuUtilization()

#include "linux_parser.h"

#include <iostream> // remove after debugging



using std::stof;
using std::string;
using std::to_string;
using std::vector;

const string LinuxParserNew::kProcDirectoryNew{"/proc"};
const string LinuxParserNew::kCmdlineFilenameNew{"/cmdline"};
const string LinuxParserNew::kCpuinfoFilenameNew{"/cpuinfo"};
const string LinuxParserNew::kStatusFilenameNew{"/status"};
const string LinuxParserNew::kStatFilenameNew{"/stat"};
const string LinuxParserNew::kUptimeFilenameNew{"/uptime"};
const string LinuxParserNew::kMeminfoFilenameNew{"/meminfo"};
const string LinuxParserNew::kVersionFilenameNew{"/version"};
const string LinuxParserNew::kOSPathNew{"/etc/os-release"};
const string LinuxParserNew::kPasswordPathNew{"/etc/passwd"};

// BONUS: Update this to use std::filesystem
vector<int> LinuxParserNew::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectoryNew.c_str());
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
float LinuxParserNew::MemoryUtilization() { 
    string lineBuffer;
  string key, value;
  float memTotal = 1.0;
  float memFree = 0.0;
  std::ifstream filestream(kProcDirectoryNew + kMeminfoFilenameNew);
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
      }
    }
  }

  return (memTotal - memFree) / memTotal;
}

long LinuxParserNew::UpTime() {
  string uptime1, uptime2;
  string lineBuffer;
  std::ifstream stream(kProcDirectoryNew + kUptimeFilenameNew);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> uptime1 >> uptime2;
    return atol(uptime1.c_str());
  }
  return 0;
}

int LinuxParserNew::TotalProcesses() {
  string key, value;
  string lineBuffer;
  std::ifstream stream(kProcDirectoryNew + kStatFilenameNew);
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

int LinuxParserNew::RunningProcesses() {
  string key, value;
  string lineBuffer;
  std::ifstream stream(kProcDirectoryNew + kStatFilenameNew);
  if (stream.is_open()) {
    while (std::getline(stream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      linestream >> key >> value;
      if (key == "procs_running") {
        return stoi(std::string(value));
      }
    }
  }
  return 0;
}

std::string LinuxParserNew::OperatingSystem() {
  string lineBuffer;
  string key, value;
  std::ifstream filestream(kOSPathNew);
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

std::string LinuxParserNew::Kernel() {
    string os, version, kernel;
  string lineBuffer;
  std::ifstream stream(kProcDirectoryNew + kVersionFilenameNew);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

long LinuxParserNew::Jiffies() {
  return 456;
}

long LinuxParserNew::ActiveJiffies() {
  return 567;
}

long LinuxParserNew::ActiveJiffies(int pid) {
    string token;
  std::string fileName{kProcDirectoryNew + std::to_string(pid) + kStatFilenameNew};
  std::ifstream fileStream(fileName);
  std::vector<std::string> tokens;
  const char delimiter = ' ';
  if (fileStream.is_open()) {
    while (std::getline(fileStream, token, delimiter)) {
      tokens.push_back(token);
    }
  }
  long val1 = atol(tokens[13].c_str());
  long val2 = atol(tokens[14].c_str());
  long val3 = atol(tokens[15].c_str());

  return val1 + val2 + val3;
  return 678;
}

long LinuxParserNew::IdleJiffies() {
  return 789;
}

// Processes
std::string LinuxParserNew::Command(int pid) {
    string command;
  string lineBuffer;
  std::string fileName{kProcDirectoryNew + std::to_string(pid) + kCmdlineFilenameNew};
  std::ifstream stream(fileName);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    return lineBuffer;
  }
  return string(); 
}

std::string LinuxParserNew::Ram(int pid) {
    string key, value;
  string lineBuffer;
  std::string fileName{kProcDirectoryNew + std::to_string(pid) + kStatusFilenameNew};
  std::ifstream filestream(fileName);
  if (filestream.is_open()) {
    while (std::getline(filestream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          // convert from kilobytes to megabytes
          return std::to_string(atol(value.c_str())/1000);
        }
      }
    }
  }
  return string();
}


// This can eventually be made private
std::string LinuxParserNew::Uid(int pid) {
  string key, value;
  string lineBuffer;
  std::string fileName{kProcDirectoryNew + std::to_string(pid) + kStatusFilenameNew};
  std::ifstream filestream(fileName);
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

std::string LinuxParserNew::User(int pid) {
  string token;
  std::string fileName{kPasswordPathNew};
  std::ifstream filestream(fileName);
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

long int LinuxParserNew::UpTime(int pid) {
  string uptime1, uptime2;
  string lineBuffer;
  std::string fileName{kProcDirectoryNew + std::to_string(pid) + kUptimeFilenameNew};
  std::ifstream stream(fileName);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    std::istringstream linestream(lineBuffer);
    linestream >> uptime1 >> uptime2;
    return stoi(uptime1);
  }
  return 0;
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



// Total number of ticks since the last boot.
// The second term is the number of ticks per second,
// typicall 100

long LinuxParser::Jiffies() { 
  return 100; // UpTime() * sysconf(_SC_CLK_TCK);  
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function

long LinuxParser::ActiveJiffies(int pid) { 
  string token;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatFilename};
  
  std::ifstream fileStream(fileName);
  std::vector<std::string> tokens;
  const char delimiter = ' ';
  if (fileStream.is_open()) {
    while (std::getline(fileStream, token, delimiter)) {
      tokens.push_back(token);
    }
  }
  long val1 = atol(tokens[13].c_str());
  long val2 = atol(tokens[14].c_str());
  long val3 = atol(tokens[15].c_str());

  return val1 + val2 + val3;
}

// Sum all of the jiffies for the cpu
long LinuxParser::ActiveJiffies() { 
  string lineBuffer;
  std::string fileName{kProcDirectory + kStatFilename};
  std::ifstream fileStream(fileName);
  if (fileStream.is_open()) {
    while (std::getline(fileStream, lineBuffer)) {
      std::istringstream lineStream(lineBuffer);
      std::vector<std::string> jiffies;
      for (std::string jiffie; lineStream >> jiffie;) {
        jiffies.push_back(jiffie);
      }
      if (jiffies[0] == "cpu") {
        long activeJiffies = 0;
        for (unsigned int i = 1; i < jiffies.size(); ++i) {
          activeJiffies += atol(jiffies[i].c_str());
        }  
       return activeJiffies;
      }
    }
  }
  return 0; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string lineBuffer;
  std::string fileName{kProcDirectory + kStatFilename};
  std::ifstream fileStream(fileName);
  if (fileStream.is_open()) {
    while (std::getline(fileStream, lineBuffer)) {
      std::istringstream lineStream(lineBuffer);
      std::vector<std::string> jiffies;
      for (std::string jiffie; lineStream >> jiffie;) {
        jiffies.push_back(jiffie);
      }
      if (jiffies[0] == "cpu") {
        long idleJiffies = atol(jiffies[LinuxParser::kIdle_].c_str()) + 
                           atol(jiffies[LinuxParser::kIOwait_].c_str());
       return idleJiffies;
      }
    }
  }
}

// TODO: return an array of CpuUtiliztions
// Return the array of jiffies for this process

vector<string> LinuxParser::CpuUtilization() { 
  std::vector<std::string> temp;
  temp.push_back("a");
  return temp;
  /*
  // vector<string> 

  long cached_active_ticks = ActiveJiffies(1); // needs to be an array
  long cached_idle_ticks = IdleJiffies();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  long active_ticks = ActiveJiffies();
  long idle_ticks = IdleJiffies();
  long duration_active{active_ticks - cached_active_ticks};
  long duration_idle{idle_ticks - cached_idle_ticks};
  long duration(duration_active + duration_idle);
  float utilization = static_cast<float>(duration_active) / duration;
  cpuUtilizations.push_back("0.5");
  // This can be used to create the CPU utilization
  // for all the pids

  return cpuUtilizations;
  */
}
 