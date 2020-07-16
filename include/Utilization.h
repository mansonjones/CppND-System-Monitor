#ifndef UTILIZATION_INCLUDE_H
#define UTILIZATION_INCLUDE_H

#include <thread>
#include <chrono>

#include <iostream> // only needed for debugging

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

  // std::cout << " ********** activeJiffies " << activeJiffies << std::endl;
  // std::cout << " ********** cachedActiveJiffies " << cpu.getCachedActiveJiffies() << std::endl;
  
  // std::cout << " ********** idleJiffies " << idleJiffies << std::endl;
  long deltaTotalJiffies = totalJiffies - previousTotal;
  // std::cout << " ********** delta active jiffies " << deltaActiveJiffies << std::endl;
  long deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
  // std::cout << " ********** delta idle jiffies " << deltaIdleJiffies << std::endl;
  // std::cout << " ********** delta " << delta << std::endl;

  if (deltaTotalJiffies < 1) {
    // std::cout << "recompute " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    idleJiffies = cpu.IdleJiffies();
    activeJiffies = cpu.ActiveJiffies();
    totalJiffies = idleJiffies + activeJiffies;

    deltaTotalJiffies = totalJiffies - previousTotal;
    deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
    // std::cout << "new active jiffies " << activeJiffies << std::endl;
    // deltaActiveJiffies = activeJiffies - cpu.getCachedActiveJiffies();
    // deltaIdleJiffies = idleJiffies - cpu.getCachedIdleJiffies();
    // delta = deltaActiveJiffies + deltaIdleJiffies;
    // std::cout << "new delta " << delta << std::endl;
  }
  percentUtilization = 
    static_cast<float>(deltaTotalJiffies - deltaIdleJiffies)/static_cast<float>(deltaTotalJiffies);
  
  cpu.setCachedActiveJiffies(activeJiffies);
  cpu.setCachedIdleJiffies(idleJiffies);
  return percentUtilization;
}

#endif