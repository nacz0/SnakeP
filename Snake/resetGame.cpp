
#include <SFML/Graphics.hpp>
#include "heading.h"
#include <vector>

void resetGame() {
    snakeHead[0] = 0;
    snakeHead[1] = 0;

    snakeX.clear();
    snakeY.clear();
    snakeX.push_back(0);
    snakeY.push_back(0);

    pressed = sf::Keyboard::D;
    prevPressed = sf::Keyboard::P;

    createReward();
}