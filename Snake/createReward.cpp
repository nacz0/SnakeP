#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "heading.h"

void createReward() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector <int> possibleR;
    std::vector <int> snakePos;

    for (int i = 0; i < 100; i++) {
        possibleR.push_back(i);
    }
    for (int i = 0; i < snakeX.size(); i++) {
        snakePos.push_back(snakeX[i] * 10 + snakeY[i]);
    }

    std::uniform_int_distribution<> randomNum(0, 99 - snakeX.size());

    for (int i = 0; i < snakePos.size(); i++) {
        for (int j = 0; j < possibleR.size(); j++) {
            if (possibleR[j] == snakePos[i]) {
                possibleR.erase(possibleR.begin() + j);
            }
        }
    }

    int rand = possibleR[randomNum(gen)];
    r[0] = rand / 10;
    r[1] = rand % 10;

}

