#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "Utilization.h"

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/

class Process : public Utilization {
 public:
  Process(int pid);
  int Pid() const;              
  std::string User() const;                     
  std::string Command() const;    
  float CpuUtilization() const;       
  std::string Ram() const;    
  long int UpTime() const;           
  bool operator<(Process const& a) const; 
  bool operator>(Process const& a) const; 
  
  void update();

  long ActiveJiffies() const;
 private:
   int pid_;
   std::string user_;
   std::string command_;
   float cpuUtilization_;
   std::string ram_;
   long int uptime_;

};

#endif