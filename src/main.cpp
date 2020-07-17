#include "ncurses_display.h"
#include "system.h"

#include "unit_tests.h"

#include <iostream>

int main() {
  System system;
  
  
  // UnitTests::testSystem();
  // UnitTests::testProcess(1);
  // UnitTests::testLinuxParser(1);
  // UnitTests::testProcessor();

 
  NCursesDisplay::Display(system);
}