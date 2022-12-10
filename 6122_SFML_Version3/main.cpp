/*
Author: Jiahao Sun
Class: ECE6122 QSZ
Last Date Modified: 10/27/2022
Description:
 This is a Pacman Game
 
 • Display the provided pac-man.bmp at the start of the game with the extra text
     o PRESS ENTER TO START
  in the middle of the window.
 • Once the user presses the ENTER key the game starts with
     o pacman located as shown above
     o all four ghosts start at the same location as shown above (bitmaps provided)
     o place the four power ups as shown above
     o place the coins as shown above
 
 • The ghost’s initial direction is determined randomly and when a ghost hits a wall
 its new direction is chosen randomly.
 • Control the location of pacman using the left, right, up, down arrow keys. • (~10 pts) Determine a game speed that makes the game fun to play (not too slow and not to
 fast)
 • The game ends when
     o one of the ghosts comes in contact with a non-powered up pacman
     o pacman consumes all the coins
     o user presses the escape key.
 • When pacman eats a powerup he can eat ghosts for 5 seconds. Ghosts that are
 eaten are gone forever.
 • Pacman and the ghost cannot go through walls.
 • Pacman and the ghost can go through the middle tunnels on each side.
 • You do not have to handle resizing the window. Just use the image size.
 
 use following command to compile
 g++ main.cpp mapGenerate.cpp positionTranslate.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include -o pacman -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++11
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

#include "globalVariable.h"
#include "mapGenerate.h"
#include "positionTranslate.h"
#include "coinsManage.h"
#include "ghostBlueManage.h"
#include "ghostOrangeManage.h"
#include "ghostPinkManage.h"
#include "ghostRedManage.h"

int main(int argc, char const** argv)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(641, 728), "SFML window");

    // Track whether the game is running
    bool paused = true;

    // Load a sprite to display
    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/pac-man.bmp");
    
    // Create a sprite
    sf::Sprite spriteBackground;
    
    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);
    
    // Load a sprite to display
    sf::Texture textureMaze;
    textureMaze.loadFromFile("graphics/maze.bmp");
    
    // Create a sprite
    sf::Sprite spriteBackgroundMaze;
    
    // Attach the texture to the sprite
    spriteBackgroundMaze.setTexture(textureMaze);

    // Set the spriteBackground to cover the screen
    spriteBackgroundMaze.setPosition(1000, 0);

    // Make a pacman sprite
    Texture texturePacman;
    texturePacman.loadFromFile("graphics/pacman.bmp");
    Sprite spritePacman;
    spritePacman.setTexture(texturePacman);
    spritePacman.setPosition(1000, 0);
    
    // Is the pacman currently moving?
    bool pacmanActive = false;

    // How fast can the pacman run
    float pacmanSpeed = 0.0f;

    // Prepare the blue ghost
    Texture textureBlueGhost;
    textureBlueGhost.loadFromFile("graphics/blue_ghost.bmp");
    Sprite spriteBlueGhost;
    spriteBlueGhost.setTexture(textureBlueGhost);
    
    // Prepare the orange ghost
    Texture textureOrangeGhost;
    textureOrangeGhost.loadFromFile("graphics/orange_ghost.bmp");
    Sprite spriteOrangeGhost;
    spriteOrangeGhost.setTexture(textureOrangeGhost);
    
    // Prepare the pink ghost
    Texture texturePinkGhost;
    texturePinkGhost.loadFromFile("graphics/pink_ghost.bmp");
    Sprite spritePinkGhost;
    spritePinkGhost.setTexture(texturePinkGhost);
    
    // Prepare the red ghost
    Texture textureRedGhost;
    textureRedGhost.loadFromFile("graphics/red_ghosts.bmp");
    Sprite spriteRedGhost;
    spriteRedGhost.setTexture(textureRedGhost);
    
    // Show PRESS ENTER TO START text
    sf::Text messageText;
    sf::Text scoreText;

    // We need to choose a font
    sf::Font font;
    font.loadFromFile("sansation.ttf");

    // Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);

    // Assign the actual message
    messageText.setString("PRESS ENTER TO START");
    scoreText.setString("Score = 0");

    // Make it really big
    messageText.setCharacterSize(40);
    scoreText.setCharacterSize(40);

    // Choose a color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);

    messageText.setPosition(320 / 1.0f, 360 / 1.0f);
    
    // Variables to control time itself
    Clock clock;
    
    // Map related parameter preparation
    // Generate map in vector
    pacmanMap = mapGenerate();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            
            if (gameOver)
            {
                window.close();
            }
            
            if (gameWin)
            {
                window.close();
            }
        }
        
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        // Start the game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            // When user pressed "Return"
            // a pacman will show
            // four ghost will show
            // coins and power up will show
            spriteBackground.setPosition(1000, 0);
            spriteBackgroundMaze.setPosition(0, 0);
            paused = false;
            spritePacman.setPosition(303, 492);
        }
        
        // set varibale dt to manage time related paramters
        Time dt = clock.restart();
        pacmanSpeed = 100;
        
        if (timePowerUpRemaining > 0)
        {
            // count down 5 seconds
            timePowerUpRemaining -= dt.asSeconds();
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
        {
            // when the right key is pressed
            // translate pacman position from pixel into vectors
            pacmanCoordinationRow = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[0];
            pacmanCoordinationColumn = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[1];

            if (interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 1)[0] || gameWin || gameOver)
            {
                // stop pacman when there is a wall on moving direction, or game is win or lose
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y);
            }
            else if (spritePacman.getPosition().x == 641)
            {
                // pacman go through tunnels
                spritePacman.setPosition(0, spritePacman.getPosition().y);
            }
            else if (!interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 1)[3])
            {
                // shift pacman to the exact pixel postion when it meets a cross road
                spritePacman.setPosition(spritePacman.getPosition().x + 0.25, pacmanPositionYArray[pacmanCoordinationRow - 1]);
            }
            else
            {
                // control pacman moving forward is there is no wall
                spritePacman.setPosition(spritePacman.getPosition().x + 0.25, spritePacman.getPosition().y);
            }
        }
        
        if (!Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
        {
            // when the left key is pressed
            // translate pacman position from pixel into vectors
            pacmanCoordinationRow = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[0];
            pacmanCoordinationColumn = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[1];
        
            if (interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 2)[0] || gameWin || gameOver)
            {
                // stop pacman when there is a wall on moving direction, or game is win or lose
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y);
                
            }
            else if (spritePacman.getPosition().x == 0)
            {
                // pacman go through tunnels
                spritePacman.setPosition(641, spritePacman.getPosition().y);
            }
            else if (!interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 2)[3])
            {
                // shift pacman to the exact pixel postion when it meets a cross road
                spritePacman.setPosition(spritePacman.getPosition().x - 0.25, pacmanPositionYArray[pacmanCoordinationRow - 1]);
            }
            else
            {
                // control pacman moving forward is there is no wall
                spritePacman.setPosition(spritePacman.getPosition().x - 0.25, spritePacman.getPosition().y);
            }
        }
        
        if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
        {
            // when the up key is pressed
            // translate pacman position from pixel into vectors
            pacmanCoordinationRow = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[0];
            pacmanCoordinationColumn = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[1];
        
            if (interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 3)[0] || gameWin || gameOver)
            {
                // stop pacman when there is a wall on moving direction, or game is win or lose
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y);
            }
            else if (!interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 3)[3])
            {
                // shift pacman to the exact pixel postion when it meets a cross road
                spritePacman.setPosition(pacmanPositionXArray[pacmanCoordinationColumn - 1], spritePacman.getPosition().y - 0.25);
            }
            else
            {
                // control pacman moving forward is there is no wall
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y - 0.25);
            }
        }
        
        if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Down))
        {
            // when the down key is pressed
            // translate pacman position from pixel into vectors
            pacmanCoordinationRow = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[0];
            pacmanCoordinationColumn = positionTranslate(23, 13, spritePacman.getPosition().x, spritePacman.getPosition().y)[1];

            if (interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 4)[0] || gameWin || gameOver)
            {
                // stop pacman when there is a wall on moving direction, or game is win or lose
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y);
            }
            else if (!interactCheck(pacmanMap, pacmanCoordinationRow, pacmanCoordinationColumn, spritePacman.getPosition().x, spritePacman.getPosition().y, 4)[3])
            {
                // shift pacman to the exact pixel postion when it meets a cross road
                spritePacman.setPosition(pacmanPositionXArray[pacmanCoordinationColumn - 1], spritePacman.getPosition().y + 0.25);
            }
            else
            {
                // control pacman moving forward is there is no wall
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y + 0.25);
            }
        }
        
        if ((timePowerUpRemaining > 0) && (pacmanCoordinationRow == blueGhostCoordinationRow) && (pacmanCoordinationColumn == blueGhostCoordinationCol))
        {
            // pacman with poweup touch ghost, ghost cannot be alive
            aliveBlueGhost = 0;
        }
        
        if ((timePowerUpRemaining > 0) && (pacmanCoordinationRow == orangeGhostCoordinationRow) && (pacmanCoordinationColumn == orangeGhostCoordinationCol))
        {
            // pacman with poweup touch ghost, ghost cannot be alive
            aliveOrangeGhost = 0;
        }
        
        if ((timePowerUpRemaining > 0) && (pacmanCoordinationRow == pinkGhostCoordinationRow) && (pacmanCoordinationColumn == pinkGhostCoordinationCol))
        {
            // pacman with poweup touch ghost, ghost cannot be alive
            alivePinkGhost = 0;
        }
        
        if ((timePowerUpRemaining > 0) && (pacmanCoordinationRow == redGhostCoordinationRow) && (pacmanCoordinationColumn == redGhostCoordinationCol))
        {
            // pacman with poweup touch ghost, ghost cannot be alive
            aliveRedGhost = 0;
        }
        
        if ((timePowerUpRemaining == 0) && (pacmanCoordinationRow == blueGhostCoordinationRow) && (pacmanCoordinationColumn == blueGhostCoordinationCol))
        {
            // pacman without poweup touch ghost, game over
            gameOver = 1;
        }
        
        if ((timePowerUpRemaining == 0) && (pacmanCoordinationRow == orangeGhostCoordinationRow) && (pacmanCoordinationColumn == orangeGhostCoordinationCol))
        {
            // pacman without poweup touch ghost, game over
            gameOver = 1;
        }
        
        if ((timePowerUpRemaining == 0) && (pacmanCoordinationRow == pinkGhostCoordinationRow) && (pacmanCoordinationColumn == pinkGhostCoordinationCol))
        {
            // pacman without poweup touch ghost, game over
            gameOver = 1;
        }
        
        if ((timePowerUpRemaining == 0) && (pacmanCoordinationRow == redGhostCoordinationRow) && (pacmanCoordinationColumn == redGhostCoordinationCol))
        {
            // pacman without poweup touch ghost, game over
            gameOver = 1;
        }
        
        if (collectedCoins == 240)
        {
            // pacman consumes all the coins, game win
            gameWin = 1;
        }
        
        pacmanPositionX = spritePacman.getPosition().x;
        pacmanPositionY = spritePacman.getPosition().y;
        if ((spritePacman.getPosition().x == 1000) && (spritePacman.getPosition().y == 0))
        {
            // ghost hide out of the game window
            spriteBlueGhost.setPosition(1000, 0);
            spriteOrangeGhost.setPosition(1000, 0);
            spritePinkGhost.setPosition(1000, 0);
            spriteRedGhost.setPosition(1000, 0);
        }
        else if (!ghostActive)
        {
            // ghost start with a postion in the middle and choose a random direction
            ghostSpeed = (rand() % 200);
            randDirectionBlueGhost = rand() % 2;
            randDirectionOrangeGhost = rand() % 2;
            randDirectionPinkGhost = rand() % 2;
            randDirectionRedGhost = rand() % 2;
            
            spriteBlueGhost.setPosition(303, 246);
            spriteOrangeGhost.setPosition(303, 246);
            spritePinkGhost.setPosition(303, 246);
            spriteRedGhost.setPosition(303, 246);
            ghostActive = true;
        }
        
        else
        {
            // manage four ghost movements
            ghostBlueManage(spriteBlueGhost);
            
            ghostOrangeManage(spriteOrangeGhost);
            
            ghostPinkManage(spritePinkGhost);
            
            ghostRedManage(spriteRedGhost);
        }
        
        /*
        ****************************************
        Update the scene
        ****************************************
        */

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(spriteBackground);
        window.draw(spriteBackgroundMaze);

        if (paused)
        {
            // Draw our message
            window.draw(messageText);
        }
        
        // Draw the pacman
        window.draw(spritePacman);
        
        if (!paused)
        {
            coinsManage(window, spritePacman.getPosition().x, spritePacman.getPosition().y);
        }
        
        // Draw ghosts
        if (aliveBlueGhost)
        {
            // draw ghost if it is alive
            window.draw(spriteBlueGhost);
        }
        if (aliveOrangeGhost)
        {
            // draw ghost if it is alive
            window.draw(spriteOrangeGhost);
        }
        if (alivePinkGhost)
        {
            // draw ghost if it is alive
            window.draw(spritePinkGhost);
        }
        if (aliveRedGhost)
        {
            // draw ghost if it is alive
            window.draw(spriteRedGhost);
        }

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
