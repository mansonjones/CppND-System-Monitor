#ifndef CPUMEASUREMENT_INCLUDE_H
#define CPUMEASUREMENT_INCLUDE_H


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

#endif