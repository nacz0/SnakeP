#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "heading.h"

int r[2];
std::vector <int> snakeX = { 0 };
std::vector <int> snakeY = { 0 };
int snakeHead[2] = { 0,0 };
int START_X = 460; //1920-1000=920 920/2
int START_Y = 40; //1080-1000=80 80/2;
int gameState = 0; //0 - menu, 1 - playing, 2 - dying, 3 - gameOver
char pressed = sf::Keyboard::D;
char prevPressed = sf::Keyboard::P;
sf::RenderWindow oknoAplikacji(sf::VideoMode(1920, 1080, 32), "Snake");

int main()
{
    
    sf::RectangleShape plane(sf::Vector2f(100, 100));
    sf::RectangleShape snakeBody(sf::Vector2f(80, 80));
    sf::RectangleShape snakeHeadPiece(sf::Vector2f(90, 90));

    sf::RectangleShape reward(sf::Vector2f(60, 60));
    reward.setOutlineThickness(20);
    reward.setOutlineColor(sf::Color(255, 255, 255, 0));
    reward.setFillColor(sf::Color(0, 0, 255));
    reward.setPosition(START_X + (r[0] * 100) + 20, START_Y + (r[0] * 100) + 20);
    
    snakeHeadPiece.setOutlineThickness(5);
    snakeHeadPiece.setOutlineColor(sf::Color(255, 255, 255, 0));

    snakeBody.setFillColor(sf::Color(255, 0, 0));
    snakeBody.setOutlineThickness(10);
    snakeBody.setOutlineColor(sf::Color(255, 255, 255,0));

    sf::Clock clock;
    int helperTime = 0;
    
    sf::Font font;
    if (!font.loadFromFile("fixedsys.ttf"))
    {
        std::cout << std::endl << "ERROR " << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(140);

    int choosedDiff = 0;
    bool blink = false;
    std::string  difficulties[3] = { "Easy","Normal","Hard" };
    int speed[3] = { 400,300,200 };
    bool canRestart = false;

    resetGame();

    while (oknoAplikacji.isOpen())
    {

        sf::Event zdarzenie;
        oknoAplikacji.clear(sf::Color(206, 240, 245));
        sf::Time time1 = clock.getElapsedTime();
        
        if (gameState==1 || gameState==2) {

            text.setString("SNAKE");
            text.setCharacterSize(140);
            text.setPosition(50, 50);
            text.setFillColor(sf::Color(0, 255, 0));
            oknoAplikacji.draw(text);

            text.setString("Score:"+ std::to_string(snakeX.size()-1));
            text.setCharacterSize(100);
            text.setPosition(1500, 50);
            text.setFillColor(sf::Color(204, 209, 217));
            oknoAplikacji.draw(text);
     
            for (int i = START_X; i < START_X+1000; i += 100) {
                for (int j = START_Y; j < START_Y+1000; j += 100) {
                    plane.setPosition(i, j);
                
                    if ((i / 100 + j / 100) % 2 == 0) { 
                        plane.setFillColor(sf::Color(101, 240, 31));
                    }
                    else {
                        plane.setFillColor(sf::Color(102, 199, 28));
                    }
                
                    oknoAplikacji.draw(plane);
                }
            }
            reward.setPosition(START_X + (r[0] * 100) + 20, START_Y + (r[1] * 100) + 20);
            oknoAplikacji.draw(reward);

            snakeHeadPiece.setFillColor(blink ? sf::Color(255, 255, 255) : sf::Color(255, 102, 0));
            snakeHeadPiece.setPosition(START_X + (snakeX[0] * 100) + 5, START_Y + (snakeY[0] * 100) + 5);
            oknoAplikacji.draw(snakeHeadPiece);

            for (int i = 1; i < snakeX.size(); i++) {
                snakeBody.setPosition(START_X + (snakeX[i] * 100) + 10, START_Y + (snakeY[i] * 100) + 10);
                oknoAplikacji.draw(snakeBody);
            }
            if (snakeX.size()>1) oknoAplikacji.draw(snakeBody);

            if (gameState==1) {
            while (oknoAplikacji.pollEvent(zdarzenie))
            {
                if (zdarzenie.type == sf::Event::Closed)
                    oknoAplikacji.close();

                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
                    oknoAplikacji.close();

                if (zdarzenie.type == sf::Event::KeyPressed &&
                    (zdarzenie.key.code == sf::Keyboard::W || zdarzenie.key.code == sf::Keyboard::S
                        || zdarzenie.key.code == sf::Keyboard::A || zdarzenie.key.code == sf::Keyboard::D))

                    pressed = zdarzenie.key.code;

            }

            if (time1.asMilliseconds() > speed[choosedDiff]) {
                clock.restart();
                switch (pressed) {
                case sf::Keyboard::W:
                    if (prevPressed == sf::Keyboard::S) {
                        pressed = sf::Keyboard::S;
                        snakeHead[1]++;
                    }
                    else {
                        snakeHead[1]--;
                    }
                    break;
                case sf::Keyboard::S:
                    if (prevPressed == sf::Keyboard::W) {
                        pressed = sf::Keyboard::W;
                        snakeHead[1]--;
                    }
                    else {
                        snakeHead[1]++;
                    }
                    break;
                case sf::Keyboard::A:
                    if (prevPressed == sf::Keyboard::D) {
                        pressed = sf::Keyboard::D;
                        snakeHead[0]++;
                    }
                    else {
                        snakeHead[0]--;
                    }
                    break;
                case sf::Keyboard::D:
                    if (prevPressed == sf::Keyboard::A) {
                        pressed = sf::Keyboard::A;
                        snakeHead[0]--;
                    }
                    else {
                        snakeHead[0]++;
                    }
                    break;
                }
                checkIfDead();
                if (gameState == 1) {
                    prevPressed = pressed;
                    snakeX.insert(snakeX.begin(), snakeHead[0]);
                    snakeY.insert(snakeY.begin(), snakeHead[1]);
                    checkIfReward();
                }
                }
            
            }
            if (gameState == 2) {
                sf::Time timeToSnakeBlink = clock.getElapsedTime();
                while (oknoAplikacji.pollEvent(zdarzenie))
                {
                    if (zdarzenie.type == sf::Event::Closed)
                        oknoAplikacji.close();

                    if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
                        oknoAplikacji.close();
                }
                if (timeToSnakeBlink.asMilliseconds() > 200) {
                    helperTime += 200;
                    if (helperTime > 1500) {
                        helperTime = 0;
                        gameState = 3;
                    }
                    clock.restart();
                    blink = !blink;
                    timeToSnakeBlink = sf::milliseconds(0);
                }
            }
        }
        if (gameState == 0) {
            while (oknoAplikacji.pollEvent(zdarzenie))
            {
                if (zdarzenie.type == sf::Event::Closed)
                    oknoAplikacji.close();

                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
                    oknoAplikacji.close();

                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::W)
                    if (choosedDiff != 0) choosedDiff--;

                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::S)
                    if (choosedDiff != 2) choosedDiff++;

                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Enter)
                {
                    blink = false;
                    gameState = 1;
                }
            }
            
            text.setString("SNAKE");
            text.setCharacterSize(200);
            text.setPosition(START_X + 300, START_Y);
            text.setFillColor(sf::Color(0,255,0));
            oknoAplikacji.draw(text);
            text.setCharacterSize(140);
                for (int i = 0; i < 3; i++) {
                    text.setString(difficulties[i]);
                    text.setPosition(START_X + 350, START_Y + (i * 150)+200);
                    text.setFillColor(i == choosedDiff ? (blink ? sf::Color(255, 255, 255) : sf::Color(250, 145, 60))
                        : sf::Color(204, 209, 217));
                    oknoAplikacji.draw(text);
                }
            
            if (time1.asMilliseconds() > (blink ? 150 : 850)) {
                blink=!blink;
                clock.restart();
            }

        }

        if (gameState == 3) {
            while (oknoAplikacji.pollEvent(zdarzenie))
            {
                if (zdarzenie.type == sf::Event::Closed)
                    oknoAplikacji.close();

                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
                    oknoAplikacji.close();

                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Enter)
                {
                    if (canRestart) {
                        helperTime = 0;
                        canRestart = false;
                        gameState = 0;
                        resetGame();
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                text.setString("GAME OVER");
                text.setPosition(START_X + 270, START_Y + 350);
                text.setFillColor(sf::Color(0, 0, 0));
                oknoAplikacji.draw(text);
            }

            if (canRestart) {
                text.setString("Restart");
                text.setPosition(START_X + 320, START_Y + 500);
                text.setFillColor(blink ? sf::Color(255, 255, 255) : sf::Color(250, 145, 60));
                oknoAplikacji.draw(text);
            }

            if (time1.asMilliseconds() > (blink ? 150 : 850)) {
                helperTime += (blink ? 150 : 850);
                if (helperTime > 1900) {
                    canRestart = true;
                }
                blink = !blink;
                clock.restart();
            }

            if (time1.asMilliseconds() > 1500) {
                canRestart = true;
            }

        }
        oknoAplikacji.display();
        
    }
    return 0;
}