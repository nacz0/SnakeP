#include <SFML/Graphics.hpp>
#include "heading.h"
#include <vector>

void checkIfDead() {

    if (snakeHead[0] > 9 || snakeHead[0] < 0 || snakeHead[1] > 9 || snakeHead[1] < 0)
        gameState = 2;
    for (int i = 1; i < snakeX.size(); i++) {
        if (snakeHead[0] == snakeX[i] && snakeHead[1] == snakeY[i])
            gameState = 2;
    }
}