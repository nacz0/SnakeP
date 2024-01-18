#pragma once
extern int r[2];
extern std::vector <int> snakeX;
extern std::vector <int> snakeY;
extern int snakeHead[2];
extern int START_X;
extern int START_Y;
extern int gameState;
extern char pressed;
extern char prevPressed;

void createReward();
void checkIfReward();
void resetGame();
void checkIfDead();