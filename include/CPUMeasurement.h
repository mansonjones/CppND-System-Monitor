#ifndef CPUMEASUREMENT_INCLUDE_H
#define CPUMEASUREMENT_INCLUDE_H

#include <thread>
#include <chrono>

#include <iostream> // only needed for debugging

class CPUMeasurement {
public:
  long Jiffies() const;
  virtual long ActiveJiffies() const = 0;
  long IdleJiffies() const;

  void setCachedActiveJiffies(long activeJiffies);
  long getCachedActiveJiffies() const;
  void setCachedIdleJiffies(long idleJiffies);
  long getCachedIdleJiffies() const;
protected:
  long cached_active_jiffies_;
  long cached_idle_jiffies_;
};


// Note. Eventually should make this code tighter using
// Concepts.
// This template function will only work only classes
// that are derived from CPUMeasurement.

template <class Type> float CalculateUtilization(Type cpu) {
  return 0.12345;
  /*
  float utilization{0};
  long activeJiffies = cpu.ActiveJiffies();
  // std::cout << " ********** activeJiffies " << activeJiffies << std::endl;
  // std::cout << " ********** cachedActiveJiffies " << cpu.getCachedActiveJiffies() << std::endl;
  long idleJiffies = cpu.IdleJiffies();
  // std::cout << " ********** idleJiffies " << idleJiffies << std::endl;
  long deltaActiveJiffies = activeJiffies - cpu.getCachedActiveJiffies();
  // std::cout << " ********** delta active jiffies " << deltaActiveJiffies << std::endl;
  long deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
  // std::cout << " ********** delta idle jiffies " << deltaIdleJiffies << std::endl;
  long delta = deltaActiveJiffies + deltaIdleJiffies;
  // std::cout << " ********** delta " << delta << std::endl;

  if (delta < 1) {
    // std::cout << "recompute " << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    activeJiffies = cpu.ActiveJiffies();
    idleJiffies = cpu.IdleJiffies();
    // std::cout << "new active jiffies " << activeJiffies << std::endl;
    deltaActiveJiffies = activeJiffies - cpu.getCachedActiveJiffies();
    deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
    delta = deltaActiveJiffies + deltaIdleJiffies;
    // std::cout << "new delta " << delta << std::endl;
  }
  utilization = static_cast<float>(deltaActiveJiffies/delta);
  // std::cout << "utilization =" << utilization << std::endl;
  cpu.setCachedActiveJiffies(activeJiffies);
  cpu.setCachedIdleJiffies(idleJiffies);
  return utilization;
  */
}

#endif