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

#ifndef positionTranslate_h
#define positionTranslate_h

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

int * positionTranslate(int initialRow, int initialCol, float pacmanPositionX, float pacmanPositionY);

#endif /* positionTranslate_h */
