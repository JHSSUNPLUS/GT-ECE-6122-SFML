/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
 This file has two functions.
 pinkGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
 There are four inputs:
  initialRow and initialCol are used to identify if this is a ghost.
  pacmanPositionX and pacmanPositionY are current ghost pixel position.
 One output array:
  first number is ghost row number in vector map
  second number is ghost column number in vector map
 ghostBlueManage is used to manage movement of the ghost.
 One input is ghost sprite
 */

#ifndef ghostPinkManage_h
#define ghostPinkManage_h

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
//#include "pinkGhostPositionTranslate.cpp"

using namespace sf;
using namespace std;

int * pinkGhostPositionTranslate(int initialRow, int initialCol, int pacmanPositionX, int pacmanPositionY)
{
    /*
     pinkGhostPositionTranslate can translate ghost's postition from pixel map to vector map.
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
void ghostPinkManage(Sprite& spritePinkGhost)
{
    /*
     ghostPinkManage is used to manage movement of the ghost.
     One input is ghost sprite
     */
    
    // get current ghost position
    float ghostPositionX = spritePinkGhost.getPosition().x;
    float ghostPositionY = spritePinkGhost.getPosition().y;
    
    // translate current ghost position
    pinkGhostCoordinationRow = pinkGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[0];
    pinkGhostCoordinationCol = pinkGhostPositionTranslate(11, 13, ghostPositionX, ghostPositionY)[1];
    
    if (gameWin || gameOver)
    {
        // when game win or lose, freeze ghost
        randDirectionPinkGhost = 4;
        spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y);
    }
    
    if (randDirectionPinkGhost == 0)
    {
        // in this direction, ghost go right
        if (pacmanMap[pinkGhostCoordinationRow][pinkGhostCoordinationCol + 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            randDirectionPinkGhost = rand() % 4;
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y);
        }
        else if (spritePinkGhost.getPosition().x == 641)
        {
            // ghost go through tunnels
            spritePinkGhost.setPosition(0, spritePinkGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, pinkGhostCoordinationRow, pinkGhostCoordinationCol, ghostPositionX, ghostPositionY, 1)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x + 0.2, pacmanPositionYArray[pinkGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x + 0.2, spritePinkGhost.getPosition().y);
        }
    }
    if (randDirectionPinkGhost == 1)
    {
        // in this direction, ghost go left
        if (pacmanMap[pinkGhostCoordinationRow][pinkGhostCoordinationCol - 1] == 1)
        {
            // if ghost hit a wall, choose another direction
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y);
            randDirectionPinkGhost = rand() % 4;
        }
        else if (spritePinkGhost.getPosition().x == 0)
        {
            // ghost go through tunnels
            spritePinkGhost.setPosition(641, spritePinkGhost.getPosition().y);
        }
        else if (!interactCheck(pacmanMap, pinkGhostCoordinationRow, pinkGhostCoordinationCol, ghostPositionX, ghostPositionY, 2)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x - 0.2, pacmanPositionYArray[pinkGhostCoordinationRow - 1]);
        }
        else
        {
            // just keep the direction and go foward
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x - 0.2, spritePinkGhost.getPosition().y);
        }
    }
    if (randDirectionPinkGhost == 2)
    {
        // in this direction, ghost go up
        if (pacmanMap[pinkGhostCoordinationRow - 1][pinkGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y);
            randDirectionPinkGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, pinkGhostCoordinationRow, pinkGhostCoordinationCol, ghostPositionX, ghostPositionY, 3)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spritePinkGhost.setPosition(pacmanPositionXArray[pinkGhostCoordinationCol - 1], spritePinkGhost.getPosition().y - 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y - 0.2);
        }
    }
    if (randDirectionPinkGhost == 3)
    {
        // in this direction, ghost go down
        if (pacmanMap[pinkGhostCoordinationRow + 1][pinkGhostCoordinationCol] == 1)
        {
            // if ghost hit a wall, choose another direction
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y);
            randDirectionPinkGhost = rand() % 4;
        }
        else if (!interactCheck(pacmanMap, pinkGhostCoordinationRow, pinkGhostCoordinationCol, ghostPositionX, ghostPositionY, 4)[3])
        {
            // when ghost pass a cross road, shift position to recoded position
            spritePinkGhost.setPosition(pacmanPositionXArray[pinkGhostCoordinationCol - 1], spritePinkGhost.getPosition().y + 0.2);
        }
        else
        {
            // just keep the direction and go foward
            spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y + 0.2);
        }
    }
}

#endif /* ghostPinkManage_h */
