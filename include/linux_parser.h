
#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

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

/*

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

*/
#endif