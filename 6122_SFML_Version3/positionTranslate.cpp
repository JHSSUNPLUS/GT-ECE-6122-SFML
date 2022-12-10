/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
Translate pacman's postition from pixel map to vector map.
There are four inputs:
 initialRow and initialCol are used to identify if this is a ghost or pacman.
 pacmanPositionX and pacmanPositionY are current pacman or ghost pixel position.
One output array:
 first number is pacman row number in vector map
 second number is pacman column number in vector map
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <math.h>
#include <iostream>

#include "positionTranslate.h"

using namespace sf;
using namespace std;

static int pacmanPositionXArray[26] = {43, 65, 82, 102, 124, /*1 - 5*/
                                       147, 167, 187, 210, 231, /*6 - 10*/
                                       250, 270, 291, 312, 332, /*11 - 15*/
                                       354, 373, 394, 414, 436, /*16 - 20*/
                                       452, 476, 494, 515, 530, /*21 - 25*/
                                       558}; // 1 ~ 26

static int pacmanPositionYArray[29] = {40, 63, 80, 102, 121, /*1 - 5*/
                                       146, 161, 184, 205, 221, /*6 - 10*/
                                       247, 265, 286, 306, 328, /*11 - 15*/
                                       348, 368, 389, 408, 430, /*16 - 20*/
                                       454, 467, 492, 513, 529, /*21 - 25*/
                                       553, 575, 593, 614}; // 1 ~ 29

int * positionTranslate(int initialRow, int initialCol, float pacmanPositionX, float pacmanPositionY)
{
    /*
     Translate pacman's postition from pixel map to vector map.
     There are four inputs:
      initialRow and initialCol are used to identify if this is a ghost or pacman.
      pacmanPositionX and pacmanPositionY are current pacman or ghost pixel position.
     One output array:
      first number is pacman row number in vector map
      second number is pacman column number in vector map
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
