#pragma once

#include <atomic>

/*
 * Simple Test-And-Set spinlock
 */
class spinlock {
public:
  spinlock();

  void lock();
  void unlock();
  bool try_lock();

private:
  std::atomic<bool> lock_;
};