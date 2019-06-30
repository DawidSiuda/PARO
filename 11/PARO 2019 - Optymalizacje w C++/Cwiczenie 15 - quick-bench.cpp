#include <algorithm>
#include <utility>
#include <vector>

namespace recursive {

	namespace detail {

		template<typename WeightType, typename ValueType>
		auto knapsack(std::vector<std::pair<WeightType, ValueType>> const& items, WeightType size_of_knapsack, typename std::vector<std::pair<WeightType, ValueType>>::size_type pos) {
			if ((size_of_knapsack == WeightType{}) || (pos == 0)) {
				return ValueType{};
			}

			auto const current_weight = items[pos - 1].first;

			if (current_weight > size_of_knapsack) {
				return knapsack(items, size_of_knapsack, pos - 1);
			}

			auto const current_value = items[pos - 1].second;
			auto const value_with_item = current_value + knapsack(items, size_of_knapsack - current_weight, pos - 1);
			auto const value_without_item = knapsack(items, size_of_knapsack, pos - 1);
			return std::max(value_with_item, value_without_item);
		}

	} // namespace detail

	template<typename WeightType, typename ValueType>
	auto knapsack(std::vector<std::pair<WeightType, ValueType>> const& items, WeightType size_of_knapsack) {
		return detail::knapsack(items, size_of_knapsack, items.size());
	}

} // namespace recursive

namespace dp {

	template<typename WeightType, typename ValueType>
	auto knapsack(std::vector<std::pair<WeightType, ValueType>> const& items, WeightType size_of_knapsack) {
		std::vector<std::vector<ValueType>> dp(size_of_knapsack + 1, std::vector<ValueType>(items.size() + 1));

		for (WeightType i{ 1 }; i <= size_of_knapsack; ++i) {
			for (typename std::vector<std::pair<WeightType, ValueType>>::size_type j{ 1 }; j <= items.size(); ++j) {
				auto const current_weight = items[j - 1].first;
				if (current_weight > i) {
					dp[i][j] = dp[i][j - 1];
				}
				else {
					auto const current_value = items[j - 1].second;
					auto const value_with_item = current_value + dp[i - current_weight][j - 1];
					auto const value_without_item = dp[i][j - 1]; 
					dp[i][j] = std::max(value_with_item, value_without_item);
				}
			}
		}
		return dp[size_of_knapsack][items.size()];
	}

} // namespace dp

std::vector<std::pair<int, int>> const items{
	{ 1, 5 },
	{ 2, 3 },
	{ 5, 2 },
	{ 4, 5 },
	{ 2, 3 },
	{ 1, 5 },
	{ 2, 3 },
	{ 5, 2 },
	{ 4, 5 },
	{ 2, 3 }
};
constexpr int size_of_knapsack{ 20 };

static void test_recursive_knapsack(benchmark::State& state) {
	for (auto _ : state) {
		auto result = recursive::knapsack(items, size_of_knapsack);
		benchmark::DoNotOptimize(result);
	}
}
BENCHMARK(test_recursive_knapsack);

static void test_dp_knapsack(benchmark::State& state) {
	for (auto _ : state) {
		auto result = dp::knapsack(items, size_of_knapsack);
		benchmark::DoNotOptimize(result);
	}
}
BENCHMARK(test_dp_knapsack);
