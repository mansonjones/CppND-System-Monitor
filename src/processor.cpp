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

float Processor::Utilization() {
    return CalculateUtilization<Processor>(*this);
}

long Processor::ActiveJiffies() const {
    return LinuxParser::ActiveJiffies();
}