/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
 This file has two functions.
 orangeGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
 There are four inputs:
  initialRow and initialCol are used to identify if this is a ghost.
  pacmanPositionX and pacmanPositionY are current ghost pixel position.
 One output array:
  first number is ghost row number in vector map
  second number is ghost column number in vector map
 ghostBlueManage is used to manage movement of the ghost.
 One input is ghost sprite
 */

#ifndef ghostOrangeManage_h
#define ghostOrangeManage_h

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <math.h>
#include <iostream>

#include "globalVariable.h"
//#include "interactCheck.cpp"
//#include "orangeGhostPositionTranslate.cpp"

using namespace sf;
using namespace std;

int * orangeGhostPositionTranslate(int initialRow, int initialCol, int pacmanPositionX, int pacmanPositionY)
{
    /*
     orangeGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
     There are four inputs:
      initialRow and initialCol are used to identify if this is a ghost.
      pacmanPositionX and pacmanPositionY are current ghost pixel position.
     One output array:
      first number is ghost row number in vector map
      second number is ghost column number in vector map
     */
    int pacmanPositionRow = initialRow;
    int pacmanPositionColumn = initialCol;
    static int interactResult[2] = {pacmanPositionRow, pacmanPositionColumn};
    
    for (int i = 0; i < 29 + 1; i++)
    {
        // this for loop is to check all pixel map position with recorded postion in array
        if (pacmanPositionY == pacmanPositionYArray[i])
        {
            // if current pixel map postion is equal to recorded postion in array,
            // means pacman move one unit in vector map
            pacmanPositionRow = i + 1;
            interactResult[0] = pacmanPositionRow;
        }
    }
    
    for (int i = 0; i < 26 + 1; i++)
    {
        // this for loop is to check all pixel map position with recorded postion in array
        if (pacmanPositionX == pacmanPositionXArray[i])
        {
            // if current pixel map postion is equal to recorded postion in array,
            // means pacman move one unit in vector map
            pacmanPositionColumn = i + 1;
            interactResult[1] = pacmanPositionColumn;
        }
    }
    return interactResult;
}

void ghostOrangeManage(Sprite& spriteOrangeGhost)
{
    /*
     ghostOrangeManage is used to manage movement of the ghost.
     One input is ghost sprite
     */
    
    // get current ghost position
    float ghostPositionX = spriteOrangeGhost.getPosition().x;
    float ghostPositionY = spriteOrangeGhost.getPosition().y;
    
    // translate current ghost position
    orangeGhostCoordinationRow = orangeGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[0];
    orangeGhostCoordinationCol = orangeGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[1];
    
    if (gameWin || gameOver)
    {
        // when game win or lose, freeze ghost
        randDirectionOrangeGhost = 4;
        spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y);
    }
    
    if (randDirectionOrangeGhost == 0)
    {
        // in this direction, ghost go right
        if (pacmanMap[orangeGhostCoordinationRow][orangeGhostCoordinationCol + 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            randDirectionOrangeGhost = rand() % 4;
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y);
        }
        else if (spriteOrangeGhost.getPosition().x == 641)
        {
            // ghost go through tunnels
            spriteOrangeGhost.setPosition(0, spriteOrangeGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, orangeGhostCoordinationRow, orangeGhostCoordinationCol, ghostPositionX, ghostPositionY, 1)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x + 0.2, orangeGhostPositionYArray[orangeGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x + 0.2, spriteOrangeGhost.getPosition().y);
        }
    }
    if (randDirectionOrangeGhost == 1)
    {
        // in this direction, ghost go left
        if (pacmanMap[orangeGhostCoordinationRow][orangeGhostCoordinationCol - 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y);
            randDirectionOrangeGhost = rand() % 4;
        }
        else if (spriteOrangeGhost.getPosition().x == 0)
        {
            // ghost go through tunnels
            spriteOrangeGhost.setPosition(641, spriteOrangeGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, orangeGhostCoordinationRow, orangeGhostCoordinationCol, ghostPositionX, ghostPositionY, 2)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x - 0.2, orangeGhostPositionYArray[orangeGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x - 0.2, spriteOrangeGhost.getPosition().y);
        }
    }
    if (randDirectionOrangeGhost == 2)
    {
        // in this direction, ghost go up
        if (pacmanMap[orangeGhostCoordinationRow - 1][orangeGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y);
            randDirectionOrangeGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, orangeGhostCoordinationRow, orangeGhostCoordinationCol, ghostPositionX, ghostPositionY, 3)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteOrangeGhost.setPosition(orangeGhostPositionXArray[orangeGhostCoordinationCol - 1], spriteOrangeGhost.getPosition().y - 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y - 0.2);
        }
    }
    if (randDirectionOrangeGhost == 3)
    {
        // in this direction, ghost go down
        if (pacmanMap[orangeGhostCoordinationRow + 1][orangeGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y);
            randDirectionOrangeGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, orangeGhostCoordinationRow, orangeGhostCoordinationCol, ghostPositionX, ghostPositionY, 4)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteOrangeGhost.setPosition(orangeGhostPositionXArray[orangeGhostCoordinationCol - 1], spriteOrangeGhost.getPosition().y + 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y + 0.2);
        }
    }
}

#endif /* ghostOrangeManage_h */
