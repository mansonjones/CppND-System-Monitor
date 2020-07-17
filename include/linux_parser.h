
#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace CPUStates {
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
}

// Processes
// The enum only goes up to starttime, which is the last value
// that we use.
namespace ProcessorStates {
  enum ProcessorStates {
    kPid_ = 0,
    kComm_,
    kState_,
    kPpid_,
    kPrgp_,
    kSession_,
    kTty_nr_,
    kTpgid_,
    kFlags_,
    kMinflt_,
    kCMinflt_,
    kMajflt_,
    kCMajflt_,
    kUtime_,
    kStime_,
    kCutime_,
    kCstime_,
    kPriority_,
    kNice_,
    kNum_threads_,
    kItrealvalue_,
    kStarttime_
  };
}


class LinuxParser {

public:
// Paths
  static const std::string kProcDirectory;
  static const std::string kCmdlineFilename;
  static const std::string kCpuinfoFilename;
  static const std::string kStatusFilename;
  static const std::string kStatFilename;
  static const std::string kUptimeFilename;
  static const std::string kMeminfoFilename;
  static const std::string kVersionFilename;
  static const std::string kOSPath;
  static const std::string kPasswordPath;

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

  // Process
  static std::string Command(int pid);
  static std::string Ram(int pid);
  static std::string Uid(int pid);
  static std::string User(int pid);
  static long int UpTime(int pid);
};

#endif