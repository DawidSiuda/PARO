#include <algorithm>
#include <limits>
#include <random>
#include <type_traits>
#include <utility>
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

auto const test_data = make_data<int, 10000>();

template<typename RandomIterator>
void bubble_sort(RandomIterator first, RandomIterator last) {
	while (last != first) {
		auto new_last = first;
		--last;
		for (auto it = first; it != last; ) {
			auto next = it + 1;
			if (*it > *next) {
				std::iter_swap(it, next);
				new_last = next;
			}
			it = std::move(next);
		}
		last = std::move(new_last);
	}
}

static void bubble_sort_test(benchmark::State& state) {
	for (auto _ : state) {
		auto data = test_data;
		bubble_sort(data.begin(), data.end());
		benchmark::DoNotOptimize(data);
	}
}
BENCHMARK(bubble_sort_test);

static void std_sort_test(benchmark::State& state) {
	for (auto _ : state) {
		auto data = test_data;
		std::sort(data.begin(), data.end());
		benchmark::DoNotOptimize(data);
	}
}
BENCHMARK(std_sort_test);
