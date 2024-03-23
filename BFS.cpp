#include <array>
#include <list>
#include <map>
#include <queue>

#include "GLOBAL.H"
#include "BFS.H"
#include "Cells.h"

using namespace gbl;
using std::queue;
using std::map;

bool isValid(Map<>& map, Position<> position, bool visited[][MAP::COLUMNS]) {
	unsigned short x = position.first;
	unsigned short y = position.second;

	if (x < 0 || x >= MAP::ROWS || y < 0 || y >= MAP::COLUMNS)
		return false;

	if (map[x][y] == MAP::Cell::Wall)
		return false;

	if (visited[x][y])
		return false;

	return true;
}

void bfs_search(
	unsigned short& path_length,
	unsigned short& total_checks,
	map<Position<>, Position<>>& previous_cells,
	queue<Position<>>& path_queue,
	Map<float>& distances,
	const Position<>& end_position,
	const Position<>& start_position,
	Map<>& map)
{
	bool visited[MAP::ROWS][MAP::COLUMNS];
	for (int i = 0; i < MAP::ROWS; i++) {
		for (int j = 0; j < MAP::COLUMNS; j++) {
			visited[i][j] = false;
			distances[i][j] = INT_MAX;
		}
	}

	queue<Position<>> que;
	que.push(start_position);
	distances[start_position.first][start_position.second] = 0;

	visited[start_position.first][start_position.second] = true;

	int adjacentRows[] = { -1, 0 , 1, 0 };
	int adjacentColumns[] = { 0, 1, 0, -1 };

	bool found = false;

	while (!que.empty()) {
		Position<> cell = que.front();
		que.pop();

		int x = cell.first;
		int y = cell.second;

		for (int i = 0; i < 4; i++) {
			int adjacent_x = x + adjacentRows[i];
			int adjacent_y = y + adjacentColumns[i];
			Position<> adjacent_position(adjacent_x, adjacent_y);

			if (isValid(map, adjacent_position, visited)) {
				que.push(adjacent_position);
				distances[adjacent_x][adjacent_y] = distances[x][y] + 1;
				previous_cells.insert({ adjacent_position, cell });
				visited[adjacent_x][adjacent_y] = true;
				total_checks++;

				if (adjacent_x == end_position.first && adjacent_y == end_position.second)
				{
					found = true;
					break;
				}
			}
		}
	}

	if (!found) {
		// not found
		return;
	}

	std::list<Position<>> corrected_path_sequence;
	path_length = distances[end_position.first][end_position.second];
	Position<> current_position = end_position;
	corrected_path_sequence.push_front(current_position);

	while (previous_cells[current_position] != start_position) {
		Position<> prev_pos = previous_cells[current_position];
		corrected_path_sequence.push_front(prev_pos);
		current_position = prev_pos;
	}

	for (Position<> position : corrected_path_sequence) {
		path_queue.push(position);
		map[position.first][position.second] = MAP::Cell::Path;
	}
}

void bfs_reset(bool& i_finished, unsigned short& i_path_length, unsigned short& i_total_checks, std::map<gbl::Position<>, gbl::Position<>>& i_previous_cell, std::queue<gbl::Position<>>& i_path_queue, gbl::Map<float>& i_distances, const gbl::Position<>& i_start_position, gbl::Map<>& i_map)
{
	i_finished = 0;

	i_path_length = 0;
	i_total_checks = 1;

	i_previous_cell.clear();

	std::queue<gbl::Position<>>().swap(i_path_queue);

	i_path_queue.push(i_start_position);

	i_map[i_start_position.first][i_start_position.second] = gbl::MAP::Cell::Visited;

	for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++)
	{
		for (unsigned short b = 0; b < gbl::MAP::ROWS; b++)
		{
			if (a == i_start_position.first && b == i_start_position.second)
				i_distances[a][b] = 0;
			else
				i_distances[a][b] = FLT_MAX;
		}
	}
}