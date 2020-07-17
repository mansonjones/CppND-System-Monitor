#ifndef UTILIZATION_INCLUDE_H
#define UTILIZATION_INCLUDE_H

#include <thread>
#include <chrono>

class Utilization {
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
  
  float percentUtilization{0};

  long idleJiffies = cpu.IdleJiffies();
  long activeJiffies = cpu.ActiveJiffies();
  
  long previousTotal = cpu.getCachedIdleJiffies() + cpu.getCachedActiveJiffies();
  long totalJiffies = idleJiffies + activeJiffies;
  
  long deltaTotalJiffies = totalJiffies - previousTotal;
  long deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();

  if (deltaTotalJiffies < 1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    idleJiffies = cpu.IdleJiffies();
    activeJiffies = cpu.ActiveJiffies();
    totalJiffies = idleJiffies + activeJiffies;

    deltaTotalJiffies = totalJiffies - previousTotal;
    deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
  }
  percentUtilization = 
    static_cast<float>(deltaTotalJiffies - deltaIdleJiffies)/static_cast<float>(deltaTotalJiffies);
  
  cpu.setCachedActiveJiffies(activeJiffies);
  cpu.setCachedIdleJiffies(idleJiffies);
  return percentUtilization;
}

#endif