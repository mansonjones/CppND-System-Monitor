#include "processor.h"

// These can be removed when utilization is moved into linux+parser

#include <string>
#include <vector>

#include <thread>  // Needed for delay in computing Utilization
#include <chrono>  // Needed for delay in computing Utilization

#include "linux_parser.h"

using std::string;
using std::vector;



Processor::Processor() {}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    return 0.4567;
    
    /*
    float utilization{0};
    // Create delay.  
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
}

long Processor::ActiveJiffies() const {
    return LinuxParser::ActiveJiffies();
}