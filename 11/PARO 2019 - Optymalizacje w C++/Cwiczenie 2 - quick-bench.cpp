#include <algorithm>
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

auto const test_data = make_data<int, 10000>();

template<typename RandomIterator>
void sift_down(RandomIterator first, typename std::iterator_traits<RandomIterator>::difference_type start, typename std::iterator_traits<RandomIterator>::difference_type end) {
	auto root = start;
	while (2 * root + 1 <= end) {
		auto const child = 2 * root + 1;
		auto swap = root;
		if (*(first + swap) < *(first + child)) {
			swap = child;
		}
		if ((child + 1 <= end) && (*(first + swap) < *(first + child + 1))) {
			swap = child + 1;
		}
		if (swap == root) {
			return;
		}
		else {
			std::iter_swap(first + root, first + swap);
			root = std::move(swap);
		}
	}
}

template<typename RandomIterator>
void heapify(RandomIterator first, typename std::iterator_traits<RandomIterator>::difference_type count) {
	auto start = (count - 1) / 2;
	while (start >= 0) {
		sift_down(first, start, count - 1);
		--start;
	}
}

template<typename RandomIterator>
void heapsort(RandomIterator first, RandomIterator last) {
	auto const count = last - first;
	heapify(first, count);
	auto end = count - 1;
	while (end > 0) {
		std::iter_swap(first + end, first);
		--end;
		sift_down(first, 0, end);
	}
}

static void heapsort_test(benchmark::State& state) {
	for (auto _ : state) {
		auto data = test_data;
		heapsort(data.begin(), data.end());
		benchmark::DoNotOptimize(data);
	}
}
BENCHMARK(heapsort_test);

static void std_sort_test(benchmark::State& state) {
	for (auto _ : state) {
		auto data = test_data;
		std::sort(data.begin(), data.end());
		benchmark::DoNotOptimize(data);
	}
}
BENCHMARK(std_sort_test);
