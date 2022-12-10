/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
Here are all used global variables
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <fstream>
#include <math.h>
using namespace sf;
using namespace std;

#ifndef globalVariable_h
#define globalVariable_h

// a vector maze map
vector<vector<int> > pacmanMap;

// initiallize pacman coordination in vector map
int pacmanCoordinationRow = 23; // Row
int pacmanCoordinationColumn = 13; // Column
int rowNumber = 28;
int columnNumber = 31;

// ghost coordination in vector map
int blueGhostCoordinationRow = 11;
int blueGhostCoordinationCol = 13;
int orangeGhostCoordinationRow = 11;
int orangeGhostCoordinationCol = 13;
int pinkGhostCoordinationRow = 11;
int pinkGhostCoordinationCol = 13;
int redGhostCoordinationRow = 11;
int redGhostCoordinationCol = 13;

// pacman position in pixel map
float pacmanPositionX;
float pacmanPositionY;

// Used in positionTranslate
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

static int blueGhostPositionXArray[26] = {43, 65, 82, 102, 124, /*1 - 5*/
                                       147, 167, 187, 210, 231, /*6 - 10*/
                                       250, 270, 291, 312, 332, /*11 - 15*/
                                       354, 373, 394, 414, 436, /*16 - 20*/
                                       452, 476, 494, 515, 530, /*21 - 25*/
                                       558}; // 1 ~ 26

static int blueGhostPositionYArray[29] = {40, 63, 80, 102, 121, /*1 - 5*/
                                       146, 161, 184, 205, 221, /*6 - 10*/
                                       247, 265, 286, 306, 328, /*11 - 15*/
                                       348, 368, 389, 408, 430, /*16 - 20*/
                                       454, 467, 492, 513, 529, /*21 - 25*/
                                       553, 575, 593, 614}; // 1 ~ 29

static int orangeGhostPositionXArray[26] = {43, 65, 82, 102, 124, /*1 - 5*/
                                       147, 167, 187, 210, 231, /*6 - 10*/
                                       250, 270, 291, 312, 332, /*11 - 15*/
                                       354, 373, 394, 414, 436, /*16 - 20*/
                                       452, 476, 494, 515, 530, /*21 - 25*/
                                       558}; // 1 ~ 26

static int orangeGhostPositionYArray[29] = {40, 63, 80, 102, 121, /*1 - 5*/
                                       146, 161, 184, 205, 221, /*6 - 10*/
                                       247, 265, 286, 306, 328, /*11 - 15*/
                                       348, 368, 389, 408, 430, /*16 - 20*/
                                       454, 467, 492, 513, 529, /*21 - 25*/
                                       553, 575, 593, 614}; // 1 ~ 29

// are ghosts active?
bool ghostActive = false;

// initialize ghost speed
float ghostSpeed = 0.0f;

// initialize ghost direction
int randDirectionBlueGhost;
int randDirectionOrangeGhost;
int randDirectionPinkGhost;
int randDirectionRedGhost;

// is every ghost alive
bool aliveBlueGhost = true;
bool aliveOrangeGhost = true;
bool alivePinkGhost = true;
bool aliveRedGhost = true;

// game state
bool gameOver = false;
bool gameWin = false;

// time of power up
float timePowerUpRemaining = 0;

// collected coins
int collectedCoins = 0;

#endif /* globalVariable_h */
