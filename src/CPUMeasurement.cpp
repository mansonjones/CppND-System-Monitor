/*
#include "CPUMeasurement.h"
#include "linux_parser.h"

#include <vector>
#include <thread>  
#include <chrono>

long CPUMeasurement::Jiffies() const {
    return LinuxParser::Jiffies();
}

long CPUMeasurement::IdleJiffies() const {
    return LinuxParser::IdleJiffies();
}

void CPUMeasurement::setCachedActiveJiffies(long activeJiffies) {
    cached_active_jiffies_ = activeJiffies;
}

long CPUMeasurement::getCachedActiveJiffies() const {
    return cached_active_jiffies_;
}

void CPUMeasurement::setCachedIdleJiffies(long idleJiffies) {
    cached_idle_jiffies_ = idleJiffies;
}

long CPUMeasurement::getCachedIdleJiffies() const {
    return cached_idle_jiffies_;
}
*/