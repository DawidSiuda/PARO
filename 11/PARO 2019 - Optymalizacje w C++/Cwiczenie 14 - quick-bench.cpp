#include <vector>

template<typename IntegralType>
IntegralType fibonacci_recursive(IntegralType n) {
	if (n <= 1) {
		return 1;
	}
	else {
		return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
	}
}

template<typename IntegralType>
IntegralType fibonacci_memoization_recursive_detail(IntegralType n, std::vector<IntegralType>& memo) {
	if (memo[n] == IntegralType{}) {
		memo[n] = fibonacci_memoization_recursive_detail(n - 1, memo) + fibonacci_memoization_recursive_detail(n - 2, memo);
		return memo[n];
	}
	else {
		return memo[n];
	}
}

template<typename IntegralType>
IntegralType fibonacci_memoization_recursive(IntegralType n) {
	auto memo = std::vector<IntegralType>(n + 1);
	memo[0] = 1;
	memo[1] = 1;
	return fibonacci_memoization_recursive_detail(n, memo);
}

template<typename IntegralType>
IntegralType fibonacci_memoization(IntegralType n) {
	auto memo = std::vector<IntegralType>(n + 1);
	memo[0] = 1;
	memo[1] = 1;
	for (IntegralType i{ 2 }; i <= n; ++i) {
		memo[i] = memo[i - 1] + memo[i - 2];
	}
	return memo[n];
}

constexpr int value{ 20 };

static void test_fibonacci_recursive(benchmark::State& state) {
	for (auto _ : state) {
		auto result = fibonacci_recursive(value);
		benchmark::DoNotOptimize(result);
	}
}
BENCHMARK(test_fibonacci_recursive);

static void test_fibonacci_memoization_recursive(benchmark::State& state) {
	for (auto _ : state) {
		auto result = fibonacci_memoization_recursive(value);
		benchmark::DoNotOptimize(result);
	}
}
BENCHMARK(test_fibonacci_memoization_recursive);

static void test_fibonacci_memoization(benchmark::State& state) {
	for (auto _ : state) {
		auto result = fibonacci_memoization(value);
		benchmark::DoNotOptimize(result);
	}
}
BENCHMARK(test_fibonacci_memoization);
