#include "processor.h"

// These can be removed when utilization is moved into linux+parser

#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor() : 
cached_active_ticks_(LinuxParser::ActiveJiffies()), 
cached_idle_ticks_(LinuxParser::IdleJiffies()) {}
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    return 0.4567;
    /*
    float utilization{0};
    long active_ticks = LinuxParser::ActiveJiffies();
    long idle_ticks = LinuxParser::IdleJiffies();
    long duration_active{active_ticks - cached_active_ticks_};
    long duration_idle{idle_ticks - cached_idle_ticks_};
    long duration(duration_active + duration_idle);
    utilization = static_cast<float>(duration_active) / duration;
    cached_active_ticks_ = active_ticks;
    cached_idle_ticks_ = idle_ticks;
    return utilization;
    */
    /*
    string sCpu, sUserTime, sNiceTime, sSystemTime, sIdleTime;
    string line;
    std::ifstream stream(LinuxParser::kProcDirectory +  LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> sCpu >> sUserTime >> sNiceTime >> sSystemTime >> sIdleTime;
        float userTime = atof(sUserTime.c_str());
        float niceTime = atof(sNiceTime.c_str());
        float systemTime = atof(sSystemTime.c_str());
        float idleTime = atof(sIdleTime.c_str());
        float total = (userTime + niceTime + systemTime + idleTime);
        return total;
    }
    return 0.65; 
    */
   // return 0.65;
}