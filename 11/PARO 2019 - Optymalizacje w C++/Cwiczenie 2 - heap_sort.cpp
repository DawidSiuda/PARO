#include <algorithm>
#include <iterator>
#include <utility>

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
