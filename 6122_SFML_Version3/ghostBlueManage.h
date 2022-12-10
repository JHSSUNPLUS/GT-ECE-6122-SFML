/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
 This file has two functions.
 blueGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
 There are four inputs:
  initialRow and initialCol are used to identify if this is a ghost.
  pacmanPositionX and pacmanPositionY are current ghost pixel position.
 One output array:
  first number is ghost row number in vector map
  second number is ghost column number in vector map
 ghostBlueManage is used to manage movement of the ghost.
 One input is ghost sprite
 */

#ifndef ghostBlueManage_h
#define ghostBlueManage_h

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <math.h>
#include <iostream>

#include "globalVariable.h"
#include "interactCheck.h"

using namespace sf;
using namespace std;

int * blueGhostPositionTranslate(int initialRow, int initialCol, int pacmanPositionX, int pacmanPositionY)
{
    /*
     blueGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
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

void ghostBlueManage(Sprite& spriteBlueGhost)
{
    /*
     ghostBlueManage is used to manage movement of the ghost.
     One input is ghost sprite
     */
    
    // get current ghost position
    float ghostPositionX = spriteBlueGhost.getPosition().x;
    float ghostPositionY = spriteBlueGhost.getPosition().y;
    
    // translate current ghost position
    blueGhostCoordinationRow = blueGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[0];
    blueGhostCoordinationCol = blueGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[1];
    
    if (gameWin || gameOver)
    {
        // when game win or lose, freeze ghost
        randDirectionBlueGhost = 4;
        spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y);
    }
    
    if (randDirectionBlueGhost == 0)
    {
        // in this direction, ghost go right
        if (pacmanMap[blueGhostCoordinationRow][blueGhostCoordinationCol + 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            randDirectionBlueGhost = rand() % 4;
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y);
        }
        else if (spriteBlueGhost.getPosition().x == 641)
        {
            // ghost go through tunnels
            spriteBlueGhost.setPosition(0, spriteBlueGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, blueGhostCoordinationRow, blueGhostCoordinationCol, ghostPositionX, ghostPositionY, 1)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x + 0.2, blueGhostPositionYArray[blueGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x + 0.2, spriteBlueGhost.getPosition().y);
        }
    }
    if (randDirectionBlueGhost == 1)
    {
        // in this direction, ghost go left
        if (pacmanMap[blueGhostCoordinationRow][blueGhostCoordinationCol - 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y);
            randDirectionBlueGhost = rand() % 4;
        }
        else if (spriteBlueGhost.getPosition().x == 0)
        {
            // ghost go through tunnels
            spriteBlueGhost.setPosition(641, spriteBlueGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, blueGhostCoordinationRow, blueGhostCoordinationCol, ghostPositionX, ghostPositionY, 2)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x - 0.2, blueGhostPositionYArray[blueGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x - 0.2, spriteBlueGhost.getPosition().y);
        }
    }
    if (randDirectionBlueGhost == 2)
    {
        // in this direction, ghost go up
        if (pacmanMap[blueGhostCoordinationRow - 1][blueGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y);
            randDirectionBlueGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, blueGhostCoordinationRow, blueGhostCoordinationCol, ghostPositionX, ghostPositionY, 3)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteBlueGhost.setPosition(blueGhostPositionXArray[blueGhostCoordinationCol - 1], spriteBlueGhost.getPosition().y - 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y - 0.2);
        }
    }
    if (randDirectionBlueGhost == 3)
    {
        // in this direction, ghost go down
        if (pacmanMap[blueGhostCoordinationRow + 1][blueGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y);
            randDirectionBlueGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, blueGhostCoordinationRow, blueGhostCoordinationCol, ghostPositionX, ghostPositionY, 4)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteBlueGhost.setPosition(blueGhostPositionXArray[blueGhostCoordinationCol - 1], spriteBlueGhost.getPosition().y + 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y + 0.2);
        }
    }
}

#endif /* ghostBlueManage_h */
