#ifndef CPUMEASUREMENT_INCLUDE_H
#define CPUMEASUREMENT_INCLUDE_H

#include <thread>
#include <chrono>

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
  float utilization{0};
  long activeJiffies = cpu.ActiveJiffies();
  long idleJiffies = cpu.IdleJiffies();
  long deltaActiveJiffies = activeJiffies - cpu.getCachedActiveJiffies();
  long deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
  long delta = deltaActiveJiffies + deltaIdleJiffies;

  if (delta < 1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    activeJiffies = cpu.ActvieJiffies();
    idleJiffies = cpu.IdleJiffies();
    deltaActiveJiffies = activeJiffies - cpu.getCachedActiveJiffies();
    deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
    delta = deltaActiveJiffies + deltaIdleJiffies;
  }
  utilization = static_cast<float>(deltaActiveJiffies/delta);
  cpu.setCahcedActiveJiffies(activeJiffies);
  cpu.setCachedIdleJiffies(idleJiffies);
  return utilization;
}

#endif