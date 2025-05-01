#include <chrono>
#include <cmath>
#include <concepts>
#include <format>
#include <iostream>
#include <vector>

#define USE_CUSTOM_SQRT

#include "nyx/math/math.h"

// Cycle counter (platform-specific, fallback to chrono if unavailable)
#if defined(__x86_64__) && defined(__GNUC__)
#include <x86intrin.h>
inline uint64_t get_cycles() { return __rdtsc(); }
#else
inline uint64_t get_cycles() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}
#endif

template <typename T>
requires std::floating_point<T>
struct TestResult {
    T x;
    T error_nyx;
    T error_std;
    T percent_diff;
};

template <typename T1, typename T2>
requires std::floating_point<T1> && std::floating_point<T2>
void print_accuracy_results(const std::vector<TestResult<T1>>& float_results,
                           const std::vector<TestResult<T2>>& double_results) {
    std::cout << "\n=== Accuracy Comparison (Relative Error & Percent Difference) ===\n";
    std::cout << std::format("{:<50} {:<50}\n", "Float Precision (Left)", "Double Precision (Right)");
    std::cout << std::format("{:<15} {:<12} {:<12} {:<10} | {:<15} {:<12} {:<12} {:<10}\n",
                             "Input", "nyx::sqrt", "std::sqrt", "% Diff",
                             "Input", "nyx::sqrt", "std::sqrt", "% Diff");

    size_t max_size = std::max(float_results.size(), double_results.size());
    for (size_t i = 0; i < max_size; ++i) {
        std::string float_str = i < float_results.size()
            ? std::format("{:<15.6f} {:<12.6e} {:<12.6e} {:<10.6f}",
                          float_results[i].x, float_results[i].error_nyx, float_results[i].error_std,
                          float_results[i].percent_diff)
            : std::format("{:<50}", "");
        std::string double_str = i < double_results.size()
            ? std::format("{:<15.6f} {:<12.6e} {:<12.6e} {:<10.6f}",
                          double_results[i].x, double_results[i].error_nyx, double_results[i].error_std,
                          double_results[i].percent_diff)
            : "";
        std::cout << std::format("{} | {}\n", float_str, double_str);
    }
}

template <typename T>
requires std::floating_point<T>
void run_sqrt_test(std::vector<TestResult<T>>& results) {
    for (T x = 0.001; x <= 1000.0; x *= 1.1) {
        T nyx_result = nyx::sqrt(x);
        T std_result = std::sqrt(x);
        T std_inv_sqrt = static_cast<T>(1.0) / std_result;

        T error_nyx = std::abs((nyx_result - std_inv_sqrt) / std_inv_sqrt);
        T error_std = std::abs((std_result - std_inv_sqrt) / std_inv_sqrt);
        T percent_diff = 100.0 * std::abs(nyx_result - std_result) / std::abs(std_result);

        if (error_nyx > 1e-6 || error_std > 1e-6) {
            results.push_back({x, error_nyx, error_std, percent_diff});
        }
    }
}

void run_performance_test() {
    constexpr int iterations = 10'000'000;

    // Float performance
    float sum_nyx_float = 0.0f, sum_std_float = 0.0f;
    auto start_time_float = std::chrono::high_resolution_clock::now();
    uint64_t start_cycles_float = get_cycles();
    for (int i = 0; i < iterations; ++i) {
        sum_nyx_float += nyx::sqrt(static_cast<float>(i % 1000 + 1));
    }
    uint64_t end_cycles_float = get_cycles();
    auto end_time_float = std::chrono::high_resolution_clock::now();

    auto nyx_time_float_ms = std::chrono::duration<float, std::milli>(end_time_float - start_time_float).count();
    uint64_t nyx_cycles_float = end_cycles_float - start_cycles_float;

    start_time_float = std::chrono::high_resolution_clock::now();
    start_cycles_float = get_cycles();
    for (int i = 0; i < iterations; ++i) {
        sum_std_float += std::sqrt(static_cast<float>(i % 1000 + 1));
    }
    end_cycles_float = get_cycles();
    end_time_float = std::chrono::high_resolution_clock::now();

    auto std_time_float_ms = std::chrono::duration<float, std::milli>(end_time_float - start_time_float).count();
    uint64_t std_cycles_float = end_cycles_float - start_cycles_float;
    float percent_diff_float = 100.0f * std::abs(sum_nyx_float - sum_std_float) / std::abs(sum_std_float);

    // Double performance
    double sum_nyx_double = 0.0, sum_std_double = 0.0;
    auto start_time_double = std::chrono::high_resolution_clock::now();
    uint64_t start_cycles_double = get_cycles();
    for (int i = 0; i < iterations; ++i) {
        sum_nyx_double += nyx::sqrt(static_cast<double>(i % 1000 + 1));
    }
    uint64_t end_cycles_double = get_cycles();
    auto end_time_double = std::chrono::high_resolution_clock::now();

    auto nyx_time_double_ms = std::chrono::duration<double, std::milli>(end_time_double - start_time_double).count();
    uint64_t nyx_cycles_double = end_cycles_double - start_cycles_double;

    start_time_double = std::chrono::high_resolution_clock::now();
    start_cycles_double = get_cycles();
    for (int i = 0; i < iterations; ++i) {
        sum_std_double += std::sqrt(static_cast<double>(i % 1000 + 1));
    }
    end_cycles_double = get_cycles();
    end_time_double = std::chrono::high_resolution_clock::now();

    auto std_time_double_ms = std::chrono::duration<double, std::milli>(end_time_double - start_time_double).count();
    uint64_t std_cycles_double = end_cycles_double - start_cycles_double;
    double percent_diff_double = 100.0 * std::abs(sum_nyx_double - sum_std_double) / std::abs(sum_std_double);

    // Output performance results
    std::cout << std::format("\n=== Performance Comparison ({} iterations) ===\n", iterations);
    std::cout << std::format("{:<50} {:<50}\n", "Float Precision (Left)", "Double Precision (Right)");
    std::cout << std::format("{:<15} {:<12} {:<12} {:<10} | {:<15} {:<12} {:<12} {:<10}\n",
                             "Function", "Time (ms)", "Cycles", "% Diff",
                             "Function", "Time (ms)", "Cycles", "% Diff");
    std::cout << std::format("{:<15} {:<12.3f} {:<12} {:<10.6f} | {:<15} {:<12.3f} {:<12} {:<10.6f}\n",
                             "nyx::sqrt", nyx_time_float_ms, nyx_cycles_float, percent_diff_float,
                             "nyx::sqrt", nyx_time_double_ms, nyx_cycles_double, percent_diff_double);
    std::cout << std::format("{:<15} {:<12.3f} {:<12} {:<10.6f} | {:<15} {:<12.3f} {:<12} {:<10.6f}\n",
                             "std::sqrt", std_time_float_ms, std_cycles_float, percent_diff_float,
                             "std::sqrt", std_time_double_ms, std_cycles_double, percent_diff_double);
    std::cout << std::format("{:<15} {:<12.6f} {:<12} {:<10} | {:<15} {:<12.6f} {:<12} {:<10}\n",
                             "Sum (nyx)", sum_nyx_float, "", "",
                             "Sum (nyx)", sum_nyx_double, "", "");
    std::cout << std::format("{:<15} {:<12.6f} {:<12} {:<10} | {:<15} {:<12.6f} {:<12} {:<10}\n",
                             "Sum (std)", sum_std_float, "", "",
                             "Sum (std)", sum_std_double, "", "");
}

int main() {
    std::vector<TestResult<float>> float_results;
    std::vector<TestResult<double>> double_results;

    run_sqrt_test(float_results);
    run_sqrt_test(double_results);

    print_accuracy_results(float_results, double_results);
    run_performance_test();

    return 0;
}
