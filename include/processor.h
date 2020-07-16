#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Utilization.h"

class Processor : public Utilization {
 public:
  Processor();
  float Utilization(); 
  long ActiveJiffies() const;
  // TODO: Declare any necessary private members
 private:
};

#endif