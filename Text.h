#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>


#ifndef TEXT_H
#define TEXT_H

void draw_stats(const short i_x, const short i_y, const unsigned short i_path_length, sf::RenderWindow& i_window, const sf::Texture& i_font_texture);
void draw_text(const bool i_center_x, const bool i_center_y, const short i_x, const short i_y, const std::string& i_text, sf::RenderWindow& i_window, const sf::Texture& i_font_texture);

#endif 
