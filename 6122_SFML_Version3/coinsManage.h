/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
 This function is used to show coins, powerups, and messages.
 Based on pacman movement and some global variables, coins, powerups and messages will change.
 Input gameWindow is used to upadate window.
 pacmanPositionX and pacmanPositionY are current pacman postion use to interact with coins and powerups.
 */

#ifndef coinsManage_h
#define coinsManage_h

#include <math.h>
#include <iostream>

using namespace sf;
using namespace std;

#include "globalVariable.h"

void coinsManage(sf::RenderWindow& gameWindow, int pacmanPositionX, int pacmanPositionY)
{
    /*
     This function is used to show coins, powerups, and messages.
     Based on pacman movement and some global variables, coins, powerups and messages will change.
     Input gameWindow is used to upadate window.
     pacmanPositionX and pacmanPositionY are current pacman postion use to interact with coins and powerups.
     */
    // set up coins and powerups
    sf::CircleShape coins(2.f);
    coins.setFillColor(sf::Color::White);
    sf::CircleShape powerUp(5.f);
    powerUp.setFillColor(sf::Color::White);
    
    // setup message
    sf::Text messageText;
    sf::Font font;
    font.loadFromFile("sansation.ttf");
    messageText.setFont(font);
    messageText.setCharacterSize(20);
    messageText.setFillColor(Color::White);
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
    messageText.setPosition(260, 312);
    gameWindow.draw(messageText);
    
    for(int row = 1; row < 30; row++)
    {
        // scan every row
        for(int col = 1; col < 27; col++)
        {
            // scan every column
            if ((pacmanPositionX == pacmanPositionXArray[col - 1]) && (pacmanPositionY == pacmanPositionYArray[row - 1]) && (pacmanMap[row][col] == 0))
            {
                // if pacman touch coins position, corresponding 0 in vector map would become 2
                // and collected coin number would increase
                pacmanMap[row][col] = 2;
                collectedCoins++;
            }
            else if ((pacmanPositionX == pacmanPositionXArray[col - 1]) && (pacmanPositionY == pacmanPositionYArray[row - 1]) && (pacmanMap[row][col] == 3))
            {
                /*
                 if pacman eats power up
                 return coinsOutput = eatPowerup
                 */
                pacmanMap[row][col] = 4;
                timePowerUpRemaining = 5;
            }
            else if (pacmanMap[row][col] == 0)
            {
                // In the begining, draw coins, accoding to 0's position in vector map
                coins.setFillColor(sf::Color::White);
                coins.setPosition(pacmanPositionXArray[col - 1] + 15, pacmanPositionYArray[row - 1] + 15);
                gameWindow.draw(coins);
            }
            else if (pacmanMap[row][col] == 3)
            {
                // In the begining, draw powerups, accoding to 3's position in vector map
                powerUp.setFillColor(sf::Color::White);
                powerUp.setPosition(pacmanPositionXArray[col - 1] + 15, pacmanPositionYArray[row - 1] + 15);
                gameWindow.draw(powerUp);
            }
        }
    }
    
    if ((timePowerUpRemaining < 5) && (timePowerUpRemaining > 4))
    {
        // show remaning power up time
        messageText.setString("POWER UP 5");
        gameWindow.draw(messageText);
    }
    else if ((timePowerUpRemaining < 4) && (timePowerUpRemaining > 3))
    {
        // show remaning power up time
        messageText.setString("POWER UP 4");
        gameWindow.draw(messageText);
    }
    else if ((timePowerUpRemaining < 3) && (timePowerUpRemaining > 2))
    {
        // show remaning power up time
        messageText.setString("POWER UP 3");
        gameWindow.draw(messageText);
    }
    else if ((timePowerUpRemaining < 2) && (timePowerUpRemaining > 1))
    {
        // show remaning power up time
        messageText.setString("POWER UP 2");
        gameWindow.draw(messageText);
    }
    else if ((timePowerUpRemaining < 1) && (timePowerUpRemaining > 0))
    {
        // show remaning power up time
        messageText.setString("POWER UP 1");
        gameWindow.draw(messageText);
    }
    else if (gameOver)
    {
        // show GAME OVER
        messageText.setString("GAME OVER");
        gameWindow.draw(messageText);
    }
    else if (gameWin)
    {
        // show you win
        messageText.setString("**YOU WIN**");
        gameWindow.draw(messageText);
    }
}

#endif /* coinsManage_h */
