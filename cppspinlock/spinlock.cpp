#include "spinlock.hpp"

void spinlock::lock() {
  while (lock_.test_and_set(std::memory_order_acquire)) {
  }
}

bool spinlock::try_lock() {
  return !lock_.test_and_set(std::memory_order_acquire);
}

void spinlock::unlock() { lock_.clear(std::memory_order_release); }

spinlock::spinlock() : lock_{ATOMIC_FLAG_INIT} {}
