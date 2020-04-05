#include "spinlock.hpp"

void spinlock::lock() {
  while (lock_.exchange(true, std::memory_order_acquire)) {
  }
}

bool spinlock::try_lock() {
  return !lock_.exchange(true, std::memory_order_acquire);
}

void spinlock::unlock() { lock_.store(false, std::memory_order_release); }

spinlock::spinlock() : lock_{false} {}
