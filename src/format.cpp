#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;
using std::ostringstream;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function


string Format::ElapsedTime(long seconds) { 
    long hours = seconds / (60 * 60);
    seconds = seconds % (60 * 60);

    long minutes = seconds / 60;

    seconds = seconds % 60;

    ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" 
    << std::setw(2) << std::setfill('0') << minutes << ":" 
    << std::setw(2) << std::setfill('0') << seconds;

    return ss.str();
}