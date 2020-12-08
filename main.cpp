//uses 3 approaches to determine count of unique values in the collection

#include <benchmark/benchmark.h>
#include <iterator>
#include <random>
#include <unordered_set>
#include <vector>

namespace bench_helpers {

static std::vector<int> gen() {
  std::vector<int> data;
  std::random_device rd;
  std::uniform_int_distribution<int> dist(-80000, 80000);
  std::generate_n(std::back_inserter(data), 1000000, [&] { return dist(rd); });
  return data;
}

static const std::vector<int> &get_test_data() {
  static std::vector<int> test_vals(gen());
  return test_vals;
}

} // namespace bench_helpers

static void vector_sort_uniq(benchmark::State &state) {
  const auto &test_vals = bench_helpers::get_test_data();
  for (auto _ : state) {
    std::vector<int> nums(test_vals);
    // std::vector<int> nums(begin(test_vals), end(test_vals));
    std::sort(begin(nums), end(nums));
    auto last = std::unique(begin(nums), end(nums));
    auto answer = std::distance(begin(nums), last);
    (void)answer;
  }
}
BENCHMARK(vector_sort_uniq);

static void set_insertion(benchmark::State &state) {
  const auto &test_vals = bench_helpers::get_test_data();
  for (auto _ : state) {
    std::set<int> s{begin(test_vals), end(test_vals)};
    auto answer = s.size();
    (void)answer;
  }
}
BENCHMARK(set_insertion);

static void unordered_set_insertion(benchmark::State &state) {
  const auto &test_vals = bench_helpers::get_test_data();
  for (auto _ : state) {
    std::unordered_set<int> s{begin(test_vals), end(test_vals)};
    auto answer = s.size();
    (void)answer;
  }
}
BENCHMARK(unordered_set_insertion);

