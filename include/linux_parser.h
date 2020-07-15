
#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

class LinuxParser {

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