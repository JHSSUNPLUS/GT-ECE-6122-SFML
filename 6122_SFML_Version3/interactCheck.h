/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
 This function is to deal with when pacman or ghost hit a wall or a crossroad.
 Input:
 mapVec is vector maze map
 pacmanPositionRow is current pacman row number in vector map
 pacmanPositionRow is current pacman column number in vector map
 pacmanPositionX is current pacman x position in pixel map
 pacmanPositionY is current pacman y position in pixel map
 pressedKey is pressed key
 Output:
 wall show if interact a wall in a direction
 updatedPacmanPositionRow give a upadated pacman postion in vector map
 updatedPacmanPositionColumn give a upadated pacman postion in vector map
 exactPosition show if pacman or ghost intercat with a cross road and in a exact postion in array
 isTunnel show if there is a tunnel
 */

#ifndef interactCheck_h
#define interactCheck_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <math.h>
#include <iostream>

using namespace sf;
using namespace std;

int * interactCheck(vector<vector<int> > mapVec, int pacmanPositionRow, int pacmanPositionColumn, int pacmanPositionX, int pacmanPositionY, int pressedKey)
{
    /*
     This function is to deal with when pacman or ghost hit a wall or a crossroad.
     Input:
     mapVec is vector maze map
     pacmanPositionRow is current pacman row number in vector map
     pacmanPositionRow is current pacman column number in vector map
     pacmanPositionX is current pacman x position in pixel map
     pacmanPositionY is current pacman y position in pixel map
     pressedKey is pressed key
     Output:
     wall show if interact a wall in a direction
     updatedPacmanPositionRow give a upadated pacman postion in vector map
     updatedPacmanPositionColumn give a upadated pacman postion in vector map
     exactPosition show if pacman or ghost intercat with a cross road and in a exact postion in array
     isTunnel show if there is a tunnel
     */
    int wall = 1;
    int updatedPacmanPositionRow = pacmanPositionRow;
    int updatedPacmanPositionColumn = pacmanPositionColumn;
    int exactPosition = 0;
    int isTunnel = 0;
    static int interactResult[5] = {wall, updatedPacmanPositionRow, updatedPacmanPositionColumn, exactPosition, isTunnel};
    
    switch (pressedKey)
    {
            // different case repreasent different directions
        case 1:
        {
            // when right key is pressed
            if (mapVec[pacmanPositionRow][pacmanPositionColumn + 1] == 1)
            {
                // Cannot go right
                wall = 1;
                interactResult[0] = wall;
                return interactResult;
            }
            else if (pacmanPositionY == pacmanPositionYArray[pacmanPositionRow])
            {
                // find a cross road
                exactPosition = 1;
                interactResult[3] = exactPosition;
                return interactResult;
            }
            else
            {
                // remove limitation
                wall = 0;
                updatedPacmanPositionColumn = updatedPacmanPositionColumn + 1;
                interactResult[0] = wall;
                interactResult[2] = updatedPacmanPositionColumn;
                return interactResult;
            }
        }
        case 2:
        {
            // when left key is pressed
            if (mapVec[pacmanPositionRow][pacmanPositionColumn - 1] == 1)
            {
                // Cannot go left
                wall = 1;
                interactResult[0] = wall;
                return interactResult;
            }
            else if (pacmanPositionY == pacmanPositionYArray[pacmanPositionRow])
            {
                // find a cross road
                exactPosition = 1;
                interactResult[3] = exactPosition;
                return interactResult;
            }
            else
            {
                // remove limitation
                wall = 0;
                updatedPacmanPositionColumn = updatedPacmanPositionColumn - 1;
                interactResult[0] = wall;
                interactResult[2] = updatedPacmanPositionColumn;
                return interactResult;
            }
        }
        case 3:
        {
            // when up key is pressed
            if (mapVec[pacmanPositionRow - 1][pacmanPositionColumn] == 1)
            {
                // Cannot go up
                wall = 1;
                interactResult[0] = wall;
                return interactResult;
            }
            else if (pacmanPositionX == pacmanPositionXArray[pacmanPositionColumn])
            {
                // find a cross road
                exactPosition = 1;
                interactResult[3] = exactPosition;
                return interactResult;
            }
            else
            {
                // remove limitation
                wall = 0;
                updatedPacmanPositionRow = updatedPacmanPositionRow - 1;
                interactResult[0] = wall;
                interactResult[1] = updatedPacmanPositionRow;
                return interactResult;
            }
        }
        case 4:
        {
            // when down key is pressed
            if (mapVec[pacmanPositionRow + 1][pacmanPositionColumn] == 1)
            {
                // Cannot go down
                wall = 1;
                interactResult[0] = wall;
                return interactResult;
            }
            else if (pacmanPositionX == pacmanPositionXArray[pacmanPositionColumn])
            {
                // find a cross road
                exactPosition = 1;
                interactResult[3] = exactPosition;
                return interactResult;
            }
            else
            {
                // remove limitation
                wall = 0;
                updatedPacmanPositionRow = updatedPacmanPositionRow + 1;
                interactResult[0] = wall;
                interactResult[1] = updatedPacmanPositionRow;
                return interactResult;
            }
        }
    }
    return 0;
}

#endif /* interactCheck_h */
