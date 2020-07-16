#include "Utilization.h"
#include "linux_parser.h"

#include <vector>
#include <thread>  
#include <chrono>

long Utilization::Jiffies() const {
    return LinuxParser::Jiffies();
}

long Utilization::IdleJiffies() const {
    return LinuxParser::IdleJiffies();
}

void Utilization::setCachedActiveJiffies(long activeJiffies) {
    cached_active_jiffies_ = activeJiffies;
}

long Utilization::getCachedActiveJiffies() const {
    return cached_active_jiffies_;
}

void Utilization::setCachedIdleJiffies(long idleJiffies) {
    cached_idle_jiffies_ = idleJiffies;
}

long Utilization::getCachedIdleJiffies() const {
    return cached_idle_jiffies_;
}
