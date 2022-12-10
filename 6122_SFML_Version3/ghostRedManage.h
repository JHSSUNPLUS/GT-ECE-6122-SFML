/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
 This file has two functions.
 redGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
 There are four inputs:
  initialRow and initialCol are used to identify if this is a ghost.
  pacmanPositionX and pacmanPositionY are current ghost pixel position.
 One output array:
  first number is ghost row number in vector map
  second number is ghost column number in vector map
 ghostBlueManage is used to manage movement of the ghost.
 One input is ghost sprite
 */

#ifndef ghostRedManage_h
#define ghostRedManage_h

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
//#include "redGhostPositionTranslate.cpp"

using namespace sf;
using namespace std;

int * redGhostPositionTranslate(int initialRow, int initialCol, int pacmanPositionX, int pacmanPositionY)
{
    /*
     redGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
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

void ghostRedManage(Sprite& spriteRedGhost)
{
    /*
     ghostRedManage is used to manage movement of the ghost.
     One input is ghost sprite
     */
    
    // get current ghost position
    float ghostPositionX = spriteRedGhost.getPosition().x;
    float ghostPositionY = spriteRedGhost.getPosition().y;
    
    // translate current ghost position
    redGhostCoordinationRow = redGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[0];
    redGhostCoordinationCol = redGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[1];
    
    if (gameWin || gameOver)
    {
        // when game win or lose, freeze ghost
        randDirectionRedGhost = 4;
        spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y);
    }
    
    if (randDirectionRedGhost == 0)
    {
        // in this direction, ghost go right
        if (pacmanMap[redGhostCoordinationRow][redGhostCoordinationCol + 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            randDirectionRedGhost = rand() % 4;
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y);
        }
        else if (spriteRedGhost.getPosition().x == 641)
        {
            // ghost go through tunnels
            spriteRedGhost.setPosition(0, spriteRedGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, redGhostCoordinationRow, redGhostCoordinationCol, ghostPositionX, ghostPositionY, 1)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x + 0.2, pacmanPositionYArray[redGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x + 0.2, spriteRedGhost.getPosition().y);
        }
    }
    if (randDirectionRedGhost == 1)
    {
        // in this direction, ghost go left
        if (pacmanMap[redGhostCoordinationRow][redGhostCoordinationCol - 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y);
            randDirectionRedGhost = rand() % 4;
        }
        else if (spriteRedGhost.getPosition().x == 0)
        {
            // ghost go through tunnels
            spriteRedGhost.setPosition(641, spriteRedGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, redGhostCoordinationRow, redGhostCoordinationCol, ghostPositionX, ghostPositionY, 2)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x - 0.2, pacmanPositionYArray[redGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x - 0.2, spriteRedGhost.getPosition().y);
        }
    }
    if (randDirectionRedGhost == 2)
    {
        // in this direction, ghost go up
        if (pacmanMap[redGhostCoordinationRow - 1][redGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y);
            randDirectionRedGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, redGhostCoordinationRow, redGhostCoordinationCol, ghostPositionX, ghostPositionY, 3)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteRedGhost.setPosition(pacmanPositionXArray[redGhostCoordinationCol - 1], spriteRedGhost.getPosition().y - 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y - 0.2);
        }
    }
    if (randDirectionRedGhost == 3)
    {
        // in this direction, ghost go down
        if (pacmanMap[redGhostCoordinationRow + 1][redGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y);
            randDirectionRedGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, redGhostCoordinationRow, redGhostCoordinationCol, ghostPositionX, ghostPositionY, 4)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spriteRedGhost.setPosition(pacmanPositionXArray[redGhostCoordinationCol - 1], spriteRedGhost.getPosition().y + 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y + 0.2);
        }
    }
}

#endif /* ghostRedManage_h */
