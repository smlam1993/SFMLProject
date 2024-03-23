#include <array>
#include <SFML/Graphics.hpp>

#include "GLOBAL.H"
#include "MAZE.H"

void draw_maze(const unsigned short i_x,
	const unsigned short i_y,
	const gbl::Position<>& i_finish_position,
	const gbl::Position<>& i_start_position,
	sf::RenderWindow& i_window,
	sf::Sprite& i_map_sprite,
	const gbl::Map<>& i_map,
	const bool i_change_colors,
	const gbl::Map<float>& i_distances)
{
	float max_distance = FLT_MIN;

	if (1 == i_change_colors)
	{
		for (const std::array<float, gbl::MAP::ROWS>& column : i_distances)
		{
			for (const float distance : column)
			{
				if (FLT_MAX != distance)
				{
					max_distance = std::max(distance, max_distance);
				}
			}
		}
	}

	for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++)
	{
		for (unsigned short b = 0; b < gbl::MAP::ROWS; b++)
		{
			float pos_x = gbl::MAP::ORIGIN_X + i_x + a * gbl::MAP::CELL_SIZE;
			float pos_y = gbl::MAP::ORIGIN_Y + i_y + b * gbl::MAP::CELL_SIZE;
			i_map_sprite.setPosition(pos_x, pos_y);

			if (a == i_finish_position.first && b == i_finish_position.second)
			{
				i_map_sprite.setColor(sf::Color(219, 0, 0));
			}
			else if (a == i_start_position.first && b == i_start_position.second)
			{
				i_map_sprite.setColor(sf::Color(0, 219, 0));
			}
			else
			{
				gbl::MAP::Cell cell_type = i_map[a][b];

				switch (cell_type)
				{
					case gbl::MAP::Cell::Empty:
					{
						i_map_sprite.setColor(sf::Color(36, 36, 85));

						break;
					}
					case gbl::MAP::Cell::Path:
					{
						i_map_sprite.setColor(sf::Color(255, 219, 85));

						break;
					}
					case gbl::MAP::Cell::Wall:
					{
						i_map_sprite.setColor(sf::Color(255, 255, 255));
					}
				}
			}

			i_window.draw(i_map_sprite);
		}
	}
}
