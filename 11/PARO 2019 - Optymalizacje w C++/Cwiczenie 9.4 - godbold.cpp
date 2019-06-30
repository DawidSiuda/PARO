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

char const* enum_to_c_str(color v) {
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
