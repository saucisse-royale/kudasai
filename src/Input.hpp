#pragma once

namespace kds {

struct Input
{
	enum {KEY, MOUSE, MOVE} type;
	union
	{
		std::pair<std::size_t, bool> code;
		std::pair<double, double> move;
	};
};

}