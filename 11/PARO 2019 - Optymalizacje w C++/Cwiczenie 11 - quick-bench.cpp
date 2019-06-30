#include <future>
#include <iterator>
#include <limits>
#include <numeric>
#include <random>
#include <thread>
#include <type_traits>
#include <vector>

template<typename IntegralType, typename std::vector<IntegralType>::size_type size>
auto make_data() {
	static_assert(std::is_integral_v<IntegralType>, "Example implementation is limited to integral types.");

	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<IntegralType> dis{ std::numeric_limits<IntegralType>::min() };

	std::vector<IntegralType> result{};
	result.reserve(size);
	for (typename std::vector<IntegralType>::size_type i{ 0 }; i < size; ++i) {
		result.push_back(dis(gen));
	}

	return result;
}

auto const test_data = make_data<int, 1000000>();

template<typename RandomIterator>
auto sum(RandomIterator first, RandomIterator last) {
	//using value_type = typename std::iterator_traits<RandomIterator>::value_type;
	using value_type = long;
	return std::accumulate(first, last, value_type{});
}

template<typename RandomIterator>
auto parallel_sum(RandomIterator first, RandomIterator last, unsigned int number_of_threads) {
	//using value_type = typename std::iterator_traits<RandomIterator>::value_type;
	using value_type = long;

	auto const number_of_numbers{ std::distance(first, last) };

	std::vector<std::future<value_type>> parts;
	parts.reserve(number_of_threads);
	for (unsigned int i{ 0 }; i < number_of_threads; ++i) {
		auto begin = first + i * number_of_numbers / number_of_threads;
		auto end = first + (i + 1) * number_of_numbers / number_of_threads;
		parts.push_back(std::async(std::launch::async, [](auto first, auto last) { return sum(first, last); }, begin, end));
	}

	value_type result{};
	for (auto& part : parts) {
		result += part.get();
	}
	return result;
}

static void test_sum(benchmark::State& state) {
	for (auto _ : state) {
		auto result = sum(test_data.begin(), test_data.end());
		benchmark::DoNotOptimize(result);
	}
}
BENCHMARK(test_sum);

static void test_parallel_sum(benchmark::State& state) {
	for (auto _ : state) {
		auto result = parallel_sum(test_data.begin(), test_data.end(), std::thread::hardware_concurrency());
		benchmark::DoNotOptimize(result);
	}
}
BENCHMARK(test_parallel_sum);
