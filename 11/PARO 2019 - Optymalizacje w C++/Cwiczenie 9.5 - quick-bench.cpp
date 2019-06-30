#include <cstdint>
#include <map>
#include <unordered_map>

enum class color {
	black,
	maroon,
	green,
	olive,
	navy,
	purple,
	teal,
	silver,
	gray,
	red,
	lime,
	yellow,
	blue,
	fuchsia,
	aqua,
	white
};

constexpr auto all_colors = {color::black, color::maroon, color::green, color::olive, color::navy, color::purple, color::teal, color::silver, color::gray, color::red, color::lime, color::yellow, color::blue, color::fuchsia, color::aqua, color::white};

char const* enum_to_c_str_switch(color v) {
	switch (v) {
#define CASE(x) case x: return #x
		CASE(color::black);
		CASE(color::maroon);
		CASE(color::green);
		CASE(color::olive);
		CASE(color::navy);
		CASE(color::purple);
		CASE(color::teal);
		CASE(color::silver);
		CASE(color::gray);
		CASE(color::red);
		CASE(color::lime);
		CASE(color::yellow);
		CASE(color::blue);
		CASE(color::fuchsia);
		CASE(color::aqua);
		CASE(color::white);
#undef CASE
	}
}

char const* enum_to_c_str_map(color v) {
	static std::map<color, char const*> const mapping{
#define CASE(x) {x, #x}
		CASE(color::black),
		CASE(color::maroon),
		CASE(color::green),
		CASE(color::olive),
		CASE(color::navy),
		CASE(color::purple),
		CASE(color::teal),
		CASE(color::silver),
		CASE(color::gray),
		CASE(color::red),
		CASE(color::lime),
		CASE(color::yellow),
		CASE(color::blue),
		CASE(color::fuchsia),
		CASE(color::aqua),
		CASE(color::white)
#undef CASE
	};
	return mapping.find(v)->second;
}

char const* enum_to_c_str_unordered_map(color v) {
	static std::unordered_map<color, char const*> const mapping{
#define CASE(x) {x, #x}
		CASE(color::black),
		CASE(color::maroon),
		CASE(color::green),
		CASE(color::olive),
		CASE(color::navy),
		CASE(color::purple),
		CASE(color::teal),
		CASE(color::silver),
		CASE(color::gray),
		CASE(color::red),
		CASE(color::lime),
		CASE(color::yellow),
		CASE(color::blue),
		CASE(color::fuchsia),
		CASE(color::aqua),
		CASE(color::white)
#undef CASE
	};
	return mapping.find(v)->second;
}

template<typename Function>
auto test(Function function) {
	std::uintptr_t hash{0};
	for (auto const c : all_colors) {
		char const* const name{function(c)};
		hash ^= reinterpret_cast<std::uintptr_t>(name);
	}
	return hash;
}

static void test_enum_to_c_str_switch(benchmark::State& state) {
	for (auto _ : state) {
		auto hash = test([](auto c) { return enum_to_c_str_switch(c); });
		benchmark::DoNotOptimize(hash);
	}
}
BENCHMARK(test_enum_to_c_str_switch);

static void test_enum_to_c_str_map(benchmark::State& state) {
	for (auto _ : state) {
		auto hash = test([](auto c) { return enum_to_c_str_map(c); });
		benchmark::DoNotOptimize(hash);
	}
}
BENCHMARK(test_enum_to_c_str_map);

static void test_enum_to_c_str_unordered_map(benchmark::State& state) {
	for (auto _ : state) {
		auto hash = test([](auto c) { return enum_to_c_str_unordered_map(c); });
		benchmark::DoNotOptimize(hash);
	}
}
BENCHMARK(test_enum_to_c_str_unordered_map);
