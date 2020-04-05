#include "spinlock.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void non_atomic_increment(size_t &value) {
  static volatile size_t temp;

  temp = value;
  temp = temp + 1;
  std::this_thread::yield();
  value = temp;
}

void unit_test_try_lock() {
  spinlock spinlock;

  spinlock.lock();
  assert(!spinlock.try_lock());
  spinlock.unlock();
  assert(spinlock.try_lock());
  spinlock.unlock();
}

void stress_test_increment() {
  constexpr size_t threads_count = 4;
  constexpr size_t increment_per_thread = 1'000'000;

  size_t shared_value = 0;

  std::vector<std::thread> threads;

  spinlock lock;

  for (auto i = 0; i < threads_count; i++) {
    threads.emplace_back([&] {
      for (size_t i = 0; i < increment_per_thread; i++) {
        std::lock_guard<spinlock> guard(lock);
        non_atomic_increment(shared_value);
      }
    });
  }

  std::for_each(threads.begin(), threads.end(), [](auto &t) { t.join(); });

  assert(shared_value == threads_count * increment_per_thread);
}

void stress_test_try_lock_increment() {
  constexpr size_t threads_count = 4;
  constexpr size_t increment_per_thread = 1'000'000;

  size_t shared_value = 0;

  std::vector<std::thread> threads;

  spinlock lock;

  for (auto i = 0; i < threads_count; i++) {
    threads.emplace_back([&] {
      size_t succeed = 0;
      while (succeed < increment_per_thread) {
        std::unique_lock<spinlock> guard(lock, std::defer_lock);
        if (guard.try_lock()) {
          succeed++;
          non_atomic_increment(shared_value);
        }
      }
    });
  }

  std::for_each(threads.begin(), threads.end(), [](auto &t) { t.join(); });

  assert(shared_value == threads_count * increment_per_thread);
}

int main() {
  unit_test_try_lock();
  stress_test_increment();
  stress_test_try_lock_increment();
  return 0;
}