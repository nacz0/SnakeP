#include <SFML/Graphics.hpp>
#include "heading.h"

void checkIfReward() {

    if ((r[0] == snakeHead[0] && r[1] == snakeHead[1])) {
        createReward();
    }
    else {
        snakeY.pop_back();
        snakeX.pop_back();
    }
}