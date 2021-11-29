#include <benchmark/benchmark.h>

#include "list_queue_impl.hpp"
#include "stack_queue_impl.hpp"

const int kStart = 1;
const int kFinish = 10;
const int kStep = 1;
const int kNumofpushes = 1e6;

static void BM_Stack_Queue(benchmark::State& state) {
  for (auto _ : state) {
    stack_queue::Queue<int> q;
    for (int i = 0; i < kNumofpushes; ++i) {
      q.push(i);
    }
    for (int i = 0; i < kNumofpushes; ++i) {
      q.pop();
    }
  }
}
BENCHMARK(BM_Stack_Queue)
    ->DenseRange(kStart, kFinish, kStep)
    ->Unit(benchmark::kMillisecond);

static void BM_List_Queue(benchmark::State& state) {
  for (auto _ : state) {
    list_queue::Queue<int> q;
    for (int i = 0; i < kNumofpushes; ++i) {
      q.push(i);
    }
    for (int i = 0; i < kNumofpushes; ++i) {
      q.pop();
    }
  }
}
BENCHMARK(BM_List_Queue)
    ->DenseRange(kStart, kFinish, kStep)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();