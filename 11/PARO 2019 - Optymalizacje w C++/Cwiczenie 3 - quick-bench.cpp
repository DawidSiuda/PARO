#include <algorithm>
#include <array>
#include <cinttypes>
#include <cstddef>
#include <iterator>
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

auto const test_data = make_data<std::uint8_t, 10000>();

template<typename RandomIterator>
void counting_sort(RandomIterator first, RandomIterator last) {
	using value_type = typename std::iterator_traits<RandomIterator>::value_type;
	static_assert(std::is_unsigned_v<value_type>, "Example implementation is limited to unsigned integral types.");
	static_assert(std::numeric_limits<value_type>::max() < std::numeric_limits<std::size_t>::max(), "Example implementation is limited to types smaller than std::size_t.");
	using counter_type = typename std::iterator_traits<RandomIterator>::difference_type;

	constexpr auto k = static_cast<std::size_t>(std::numeric_limits<value_type>::max()) + 1;
	std::array<counter_type, k> count{};

	for (auto it = first; it != last; ++it) {
		++count[*it];
	}

	for (std::size_t i{ 0 }; i < k; ++i) {
		std::fill_n(first, count[i], i);
		first += count[i];
	}
}

static void counting_sort_test(benchmark::State& state) {
	for (auto _ : state) {
		auto data = test_data;
		counting_sort(data.begin(), data.end());
		benchmark::DoNotOptimize(data);
	}
}
BENCHMARK(counting_sort_test);

static void std_sort_test(benchmark::State& state) {
	for (auto _ : state) {
		auto data = test_data;
		std::sort(data.begin(), data.end());
		benchmark::DoNotOptimize(data);
	}
}
BENCHMARK(std_sort_test);
