#ifndef DRAW_ALL_FIGURES_HPP
#define DRAW_ALL_FIGURES_HPP

#include "../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// Główna funkcja rysująca
void drawAllFigures(PrimitiveRenderer& renderer, Player& player);

#endif // DRAW_ALL_FIGURES_HPP