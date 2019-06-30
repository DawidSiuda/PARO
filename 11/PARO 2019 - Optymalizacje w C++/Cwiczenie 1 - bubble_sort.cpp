#include <algorithm>
#include <utility>

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
