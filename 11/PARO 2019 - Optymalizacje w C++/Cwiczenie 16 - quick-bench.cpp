#include <cstring>
#include <utility>
#include <vector>

class resource {
public:
	explicit resource(std::size_t size):
		size{ size },
		buffer{ new unsigned char[size] }
	{
	}

	resource(resource&& rhs) noexcept:
		size{ rhs.size },
		buffer{ rhs.buffer }
	{
		rhs.size = 0;
		rhs.buffer = nullptr;
	}

	resource(resource const& rhs):
		size{ rhs.size },
		buffer{ new unsigned char[size] }
	{
		std::memcpy(buffer, rhs.buffer, rhs.size);
	}

	resource& operator =(resource&& rhs) noexcept {
		resource{ std::move(rhs) }.swap(*this);
		return *this;
	}

	resource& operator =(resource const& rhs) {
		resource{ rhs }.swap(*this);
		return *this;
	}

	~resource() noexcept {
		size = 0;
		delete[] buffer;
		buffer = nullptr;
	}

	void swap(resource& rhs) noexcept {
		using std::swap;
		swap(size, rhs.size);
		swap(buffer, rhs.buffer);
	}

private:
	std::size_t size;
	unsigned char* buffer;
};

void swap(resource& lhs, resource& rhs) noexcept {
	lhs.swap(rhs);
}

constexpr std::size_t buffer_size{ 1024 };

static void test_copy(benchmark::State& state) {
	for (auto _ : state) {
		resource data_1{ buffer_size };
		auto data_2 = data_1;
		benchmark::DoNotOptimize(data_2);
	}
}
BENCHMARK(test_copy);

static void test_move(benchmark::State& state) {
	for (auto _ : state) {
		resource data_1{ buffer_size };
		auto data_2 = std::move(data_1);
		benchmark::DoNotOptimize(data_2);
	}
}
BENCHMARK(test_move);
