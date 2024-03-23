#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include <Chrono>
#include <SFML/Graphics.hpp>

namespace gbl
{
	using std::chrono::microseconds;
	using std::array;
	using std::pair;

	namespace PATHFINDING
	{
		constexpr unsigned short CHECKS_PER_FRAME = 121;
	}

	namespace MAP
	{
		constexpr unsigned char CELL_SIZE = 40;
		constexpr unsigned char ORIGIN_X = 40;
		constexpr unsigned char ORIGIN_Y = 40;

		constexpr unsigned short COLUMNS = 11;
		constexpr unsigned short ROWS = 11;

		enum Cell
		{
			Empty,
			Invalid,
			Path,
			Visited,
			Wall,
			Reserved
		};
	}

	namespace SCREEN
	{
		constexpr unsigned char RESIZE = 1;

		constexpr unsigned short HEIGHT = 700;
		constexpr unsigned short WIDTH = 1000;

		constexpr microseconds FRAME_DURATION(16667);

	}

	template <typename value_type>
	char sign(const value_type i_value)
	{
		return (0 < i_value) - (0 > i_value);
	}

	template <typename value_type = MAP::Cell>
	using Map = array<array<value_type, MAP::ROWS>, MAP::COLUMNS>;

	template <typename value_type = unsigned short>
	using Position = pair<value_type, value_type>;
}
#endif