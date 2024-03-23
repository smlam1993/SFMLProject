#include <array>
#include <queue>
#include <Chrono>
#include <SFML/Graphics.hpp>
#include <random>

#include "TEXT.H"
#include "GLOBAL.H"
#include "MAZE.H"
#include "BFS.H"

using std::map;
using std::queue;
using gbl::Position;
using gbl::Map;
using gbl::MAP::Cell;
using sf::Event;
using sf::Keyboard;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::VideoMode;
using sf::View;
using sf::FloatRect;

int main()
{
	bool bfs_finished = false;

	unsigned short bfs_path_length = 0;
	unsigned short bfs_total_checks = 0;

	std::map<Position<>, Position<>> bfs_previous_cell;
	std::queue<Position<>> bfs_path_queue;

	Map<> map = {};
	Position<> start_position(0, 0);
	Position<> end_position(gbl::MAP::COLUMNS - 1, gbl::MAP::ROWS - 1);

	Map<> bfs_map = {};
	Map<float> bfs_distances = {};

	std::chrono::microseconds lag(0);

	RenderWindow window(VideoMode(gbl::SCREEN::RESIZE * gbl::SCREEN::WIDTH, gbl::SCREEN::RESIZE * gbl::SCREEN::HEIGHT), "Pathfinding", sf::Style::Close);
	window.setView(View(FloatRect(0, 0, gbl::SCREEN::WIDTH, gbl::SCREEN::HEIGHT)));

	Texture font_texture;
	font_texture.loadFromFile("Font.png");

	Texture map_texture;
	map_texture.loadFromFile("Map.png");

	// set reserved
	map[start_position.first][start_position.second] = Cell::Reserved;
	map[end_position.first][end_position.second] = Cell::Reserved;

	//set wall
	std::random_device rd;
	std::uniform_int_distribution<> dist(0, 10);
	for (int i = 0; i < map.size(); i++)
	{
		std::array<Cell, gbl::MAP::ROWS>& column = map[i];
		for (int j = 0; j < column.size(); j++) {
			if (column[j] != Cell::Empty)
				continue;

			//bool isWall = (std::rand() / (float)RAND_MAX) < 0.22F;
			bool isWall = (dist(rd) % 10) == 0;
			if (isWall) {
				column[j] = Cell::Wall;
			}
		}
	}

	bfs_map = map;

	Sprite map_sprite;
	map_sprite.setTexture(map_texture);

	bool isNotPathed = true;

	while (window.isOpen())
	{
		bool map_updated = false;

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
				{
					window.close();

					break;
				}
				case Event::KeyPressed:
				{
					switch (event.key.code)
					{
						case Keyboard::Enter: //Pause and Resume the search
						{
							isNotPathed = true;

							break;
						}
						case Keyboard::Space: //Restart the search
						{
							map_updated = true;
							isNotPathed = true;

							break;
						}
					}
				}
			}

			//Reset everything
			if (map_updated)
			{
				bfs_map = map;
				bfs_reset(bfs_finished, bfs_path_length, bfs_total_checks, bfs_previous_cell, bfs_path_queue, bfs_distances, start_position, bfs_map);
			}

			//Search
			if (isNotPathed)
			{
				bfs_search(bfs_path_length, bfs_total_checks, bfs_previous_cell, bfs_path_queue, bfs_distances, end_position, start_position, bfs_map);
				isNotPathed = false;
			}

			//Draw everything
			if (gbl::SCREEN::FRAME_DURATION > lag)
			{
				window.clear();

				draw_maze(0, 0, end_position, start_position, window, map_sprite, bfs_map, 1, bfs_distances);

				draw_stats(0.625f * gbl::SCREEN::WIDTH, 0.625f * gbl::SCREEN::HEIGHT, bfs_path_length, window, font_texture);

				window.display();
			}
		}
	}
}