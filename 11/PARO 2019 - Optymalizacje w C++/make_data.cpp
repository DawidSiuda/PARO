#include <limits>
#include <random>
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

auto const test_data = make_data<int, 10000>();
