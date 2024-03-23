#pragma once

#ifndef BFS_H
#define BFS_H

using std::map;
using std::queue;
using namespace gbl;

void bfs_search(unsigned short& i_path_length, unsigned short& i_total_checks, map<Position<>, Position<>>& i_previous_cell, queue<Position<>>& i_path_queue, Map<float>& i_distances, const Position<>& i_finish_position, const Position<>& i_start_position, Map<>& i_map);

void bfs_reset(bool& i_finished, unsigned short& i_path_length, unsigned short& i_total_checks, map<Position<>, Position<>>& i_previous_cell, queue<Position<>>& i_path_queue, Map<float>& i_distances, const Position<>& i_start_position, Map<>& i_map);

#endif