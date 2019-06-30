template<typename int_t>
constexpr auto arithmetic_sequence_sum(int_t from, int_t to, int_t increment) {
	int_t sum{};
	for (; from <= to; from += increment) {
		sum += from;
	}
	return sum;
}

auto foo(int i) {
	return arithmetic_sequence_sum(i, i + 1, 1);
}
