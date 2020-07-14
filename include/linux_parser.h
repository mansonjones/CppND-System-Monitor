
#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

class LinuxParserNew {
public:
// Paths
  static const std::string kProcDirectoryNew;
  static const std::string kCmdlineFilenameNew;
  static const std::string kCpuinfoFilenameNew;
  static const std::string kStatusFilenameNew;
  static const std::string kStatFilenameNew;
  static const std::string kUptimeFilenameNew;
  static const std::string kMeminfoFilenameNew;
  static const std::string kVersionFilenameNew;
  static const std::string kOSPathNew;
  static const std::string kPasswordPathNew;

  // System
  static float MemoryUtilization();
  static long UpTime();
  static std::vector<int> Pids();
  static int TotalProcesses();
  static int RunningProcesses();
  static std::string OperatingSystem();
  static std::string Kernel();

  
  static long Jiffies();
  static long ActiveJiffies();
  static long ActiveJiffies(int pid);
  static long IdleJiffies();

  // Processes
  static std::string Command(int pid);
  static std::string Ram(int pid);
  static std::string Uid(int pid);
  static std::string User(int pid);
  static long int UpTime(int pid);
};

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
// long UpTime();
std::vector<int> Pids();
// int TotalProcesses();
// int RunningProcesses();
// std::string OperatingSystem();
// std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 1,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};

std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
enum ProcessorStates {
  kProcPid_ = 0,
  kProcComm_,
  kProcState_,
  kProcPpid_,
  kProcPrgp_,
  kProcSession_,
  kProcTty_nr_,
  kProcTpgid_,
  kProcFlags_,
  kProcMinflt_,
  kProcMajflt_,
  kProcUtime_,
  kProcStime_,
  kProcCutime_,
  kProcCstime_,
  kProcPriority_,
  kProcNice_,
  kProcNum_threads_,
};

// std::string Command(int pid);
// std::string Ram(int pid);
std::string Uid(int pid);
// std::string User(int pid);
// long int UpTime(int pid);

};  // namespace LinuxParser

#endif