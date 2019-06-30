#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <limits>
#include <type_traits>

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
