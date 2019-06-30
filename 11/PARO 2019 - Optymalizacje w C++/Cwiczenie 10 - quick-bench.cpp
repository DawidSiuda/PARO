#include <string>

const std::string initial{"test"};
const std::string right{"me"};

static void test_add_with_assign(benchmark::State& state) {
	for (auto _ : state) {
		std::string text{initial};
		text += right;
		benchmark::DoNotOptimize(text);
	}
}
BENCHMARK(test_add_with_assign);

static void test_add(benchmark::State& state) {
	for (auto _ : state) {
		std::string text{initial};
		text = text + right;
		benchmark::DoNotOptimize(text);
	}
}
BENCHMARK(test_add);
