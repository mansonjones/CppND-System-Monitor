#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <thread> // Needed for delay in CpuUtilization()
#include <chrono> // Needed for delay in CpuUtilization()

#include <iostream> // delete after debugging

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

const string LinuxParser::kProcDirectory{"/proc/"};
const string LinuxParser::kCmdlineFilename{"/cmdline"};
const string LinuxParser::kCpuinfoFilename{"/cpuinfo"};
const string LinuxParser::kStatusFilename{"/status"};
const string LinuxParser::kStatFilename{"/stat"};
const string LinuxParser::kUptimeFilename{"/uptime"};
const string LinuxParser::kMeminfoFilename{"/meminfo"};
const string LinuxParser::kVersionFilename{"/version"};
const string LinuxParser::kOSPath{"/etc/os-release"};
const string LinuxParser::kPasswordPath{"/etc/passwd"};

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
float LinuxParser::MemoryUtilization() { 
    string lineBuffer;
  string key, value;
  float memTotal = 1.0;
  float memFree = 0.0;
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
      }
    }
  }

  return (memTotal - memFree) / memTotal;
}

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

int LinuxParser::RunningProcesses() {
  string key, value;
  string lineBuffer;
  std::ifstream stream(kProcDirectory + kStatFilename);
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

std::string LinuxParser::OperatingSystem() {
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

std::string LinuxParser::Kernel() {
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

long LinuxParser::Jiffies() {
  return ActiveJiffies() + IdleJiffies();
}

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
        long activeJiffies = 
          atol(jiffies[CPUStates::kUser_].c_str()) + 
          atol(jiffies[CPUStates::kNice_].c_str()) + 
          atol(jiffies[CPUStates::kSystem_].c_str()) + 
          atol(jiffies[CPUStates::kIRQ_].c_str()) + 
          atol(jiffies[CPUStates::kSoftIRQ_].c_str()) + 
          atol(jiffies[CPUStates::kSteal_].c_str());
       return activeJiffies;
      }
    }
  }
  return 0;
}

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
 
  return atol(tokens[ProcessorStates::kUtime_].c_str()) + 
  atol(tokens[ProcessorStates::kStime_].c_str()) +
  atol(tokens[ProcessorStates::kCutime_].c_str()) +
  atol(tokens[ProcessorStates::kCstime_].c_str()) +
  atol(tokens[ProcessorStates::kStarttime_].c_str());

}

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
        long idleJiffies = atol(jiffies[CPUStates::kIdle_].c_str()) + 
                           atol(jiffies[CPUStates::kIOwait_].c_str());
       return idleJiffies;
      }
    }
  }
}

// Processes
std::string LinuxParser::Command(int pid) {
    string command;
  string lineBuffer;
  std::string fileName{kProcDirectory + std::to_string(pid) + kCmdlineFilename};
  std::ifstream stream(fileName);
  if (stream.is_open()) {
    std::getline(stream, lineBuffer);
    return lineBuffer;
  }
  return string(); 
}

std::string LinuxParser::Ram(int pid) {
  string key, value;
  string lineBuffer;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatusFilename};
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
std::string LinuxParser::Uid(int pid) {
  string key, value;
  string lineBuffer;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatusFilename};
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

std::string LinuxParser::User(int pid) {
  string token;
  std::string fileName{kPasswordPath};
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

// UpTime in seconds
long int LinuxParser::UpTime(int pid) {
  string token;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatFilename};
  // std::cout << "fileName" << fileName << std::endl;
  std::ifstream fileStream(fileName);
  std::vector<std::string> tokens;
  const char delimiter = ' ';
  if (fileStream.is_open()) {
    while (std::getline(fileStream, token, delimiter)) {
      tokens.push_back(token);
    }
  }
 // std::cout << "token = " << tokens[ProcessorStates::kStarttime_] << std::endl;
  long upTime = atol(tokens[ProcessorStates::kStarttime_].c_str()) / static_cast<long int>(sysconf(_SC_CLK_TCK));
  return upTime;
}

