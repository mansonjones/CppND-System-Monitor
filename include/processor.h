#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "CPUMeasurement.h"

class Processor : public CPUMeasurement {
 public:
  Processor();
  float Utilization();  // TODO: See src/processor.cpp
  long ActiveJiffies() const;
  // TODO: Declare any necessary private members
 private:
};

#endif