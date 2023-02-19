#include <iostream>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Snake.h"
#include "PlayerSnake.h"
#include "Collectables.h"

sf::Vector2f Game::FreeSpacePos()
{
    int alongX = (m_screenWidth - Snake::m_headSize * 2.0f) / (int)Snake::m_headSize;
    int alongY = (m_screenHeight - Snake::m_headSize * 2.0f) / (int)Snake::m_headSize;

    sf::Vector2f pos;

    do {
        pos.x = (rand() % alongX) * Snake::m_headSize + Snake::m_headSize;
        pos.y = (rand() % alongY) * Snake::m_headSize + Snake::m_headSize;
    } while (PlaceIsTaken(pos) || pos.y < m_waterDimensions.y);
    
    return pos;
}

bool Game::PlaceIsTaken(sf::Vector2f pos) const {
    for (int i = 0; i < 30; i++) {
        if (m_collectables[i].GetAlive() && m_collectables[i].getPosition() == pos) {
            return true;
        }
    }
    for (Snake* snake : m_snakeVector) {
        if (snake->DoesCoverPlace(pos)) {
            return true;
        }
    }

    if (pos.y <= m_waterDimensions.y) {
        return true;
    }
}

//void Game::RandomlyAddACollectable()
//{
//    if (rand() % 20 == 0) {
//        int alongX = (m_screenWidth - Snake::m_headSize * 2.0f) / (int)Snake::m_headSize;
//        int alongY = (m_screenHeight - Snake::m_headSize * 2.0f) / (int)Snake::m_headSize;
//
//        for (int i = 0; i < 30; i++) {
//            if (m_collectables[i].GetAlive() == false) {
//                sf::Vector2f pos;
//                do {
//                    pos.x = (rand() % alongX) * Snake::m_headSize + Snake::m_headSize;
//                    pos.y = (rand() % alongY) * Snake::m_headSize + Snake::m_headSize;
//                } while (PlaceIsTaken(pos) || pos.y < m_waterDimensions.y);
//                m_collectables[i].Spawn(pos);
//
//                break;
//            }
//        }
//    }
//}

void Game::CheckCollectablesAboveWater(sf::Vector2f pos)
{
    sf::Vector2f newPos;

    for (int i = 0; i < 30; i++) {
        if (m_collectables->getPosition().y < pos.y) {
            newPos.x = m_collectables[i].getPosition().x;
            newPos.y = m_collectables[i].getPosition().y + Snake::m_headSize;
            m_collectables[i].setNewPosition(newPos);
        }
    }
}

void Game::Run()
{
    sf::Vector2f snake1Pos{ 100, 200 };
    sf::Vector2f snake2Pos{ 260, 360 };

    // All SFML types and functions are contained in the sf namespace

    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : A0099686");

    m_snakeVector.push_back(new PlayerSnake(snake1Pos, sf::Color::Red,0));
    m_snakeVector.push_back(new PlayerSnake(snake2Pos, sf::Color::Yellow,1));

    window.setFramerateLimit(60);
    srand(time(NULL));

    // We can still output to the console window
    std::cout << "SnakeGame: Starting" << std::endl;

    //Creates a clock from which to get an elapsed time for things like spawning collectables
    sf::Clock clock;
    clock.restart();

    sf::Clock waterClock;
    waterClock.restart();

    sf::Clock oxygenClock;
    oxygenClock.restart();

    int counter{ 0 };
    float fps{ 0 };

    int oxygenLevel1 = 100;
    int oxygenLevel2 = 100;

    m_waterDimensions = sf::Vector2f(sf::Vector2f(m_screenWidth - Snake::m_headSize * 2.0f, m_screenHeight - Snake::m_headSize * 2.0f));

    sf::RectangleShape water(m_waterDimensions);

    water.setPosition(sf::Vector2f(Snake::m_headSize, Snake::m_headSize));
    water.setFillColor(sf::Color(0, 141, 242));

    float waterStartHeight = m_screenHeight - Snake::m_headSize * 2.0f;
    float waterDropAmount = waterStartHeight / 90.0f;

    float currentWaterDrop = 0;

    int player1Score = 0;
    int player2Score = 0;

    /*sf::Music backgroundMusic;
    backgroundMusic.openFromFile("Data/SoundFX/8bit music.wav");*/

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        /*backgroundMusic.play();*/
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        // We must clear the window each time around the loop
        window.clear();

        std::string deathReason;
        std::string winnerSnake;

        //Creates text for Game Over
        sf::Font endGameFont;
        endGameFont.loadFromFile("Data/Fonts/ARCADECLASSIC.ttf");
        sf::Text gameOver;
        gameOver.setFont(endGameFont);
        gameOver.setCharacterSize(32);
        gameOver.setFillColor(sf::Color::Red);
        if (player1Score > player2Score) {
            gameOver.setString("GAME OVER \n PLAYER 1 WINS! \n BETTER LUCK NEXT TIME \n PLAYER 2");
        }
        else if (player2Score > player1Score) {
            gameOver.setString("GAME OVER \n PLAYER 2 WINS! \n BETTER LUCK NEXT TIME \n PLAYER 1");
        }
        else if (player1Score == player2Score) {
            gameOver.setString("GAME OVER \n NO WINNERS");
        }
        else {
            gameOver.setString("GAME OVER \n NO WINNERS");
        }
        gameOver.setPosition(300, 300);

        sf::Text snakeWin;
        snakeWin.setFont(endGameFont);
        snakeWin.setCharacterSize(30);
        snakeWin.setFillColor(sf::Color::White);
        snakeWin.setString(winnerSnake);

        std::string score1String = std::to_string(player1Score);
        std::string score2String = std::to_string(player2Score);

        //Creates font and text for the player 1's score to be displayed
        sf::Font player1ScoreFont;
        player1ScoreFont.loadFromFile("Data/Fonts/ARCADE.ttf");
        sf::Text player1ScoreText;
        player1ScoreText.setFont(player1ScoreFont);
        player1ScoreText.setCharacterSize(30);
        player1ScoreText.setFillColor(sf::Color::White);
        player1ScoreText.setString("Score 1: " + score1String + "            Oxygen 1: " + std::to_string(oxygenLevel1));
        player1ScoreText.setPosition({ 20.0f, 0.0f });

        //Creates font and text for player 2's score to be displayed
        sf::Font player2ScoreFont;
        player2ScoreFont.loadFromFile("Data/Fonts/ARCADE.ttf");
        sf::Text player2ScoreText;
        player2ScoreText.setFont(player2ScoreFont);
        player2ScoreText.setCharacterSize(30);
        player2ScoreText.setFillColor(sf::Color::White);
        player2ScoreText.setString("Score 2: " + score2String + "            Oxygen 2: " + std::to_string(oxygenLevel2));
        player2ScoreText.setPosition({ 20.0f, 20.0f });

        //Creates font and text for the final scores to be displayes when the snakes are dead
        sf::Font finalScoresFont;
        finalScoresFont.loadFromFile("Data/Fonts/ARCADE.ttf");
        sf::Text finalScore1;
        finalScore1.setFont(finalScoresFont);
        finalScore1.setCharacterSize(30);
        finalScore1.setFillColor(sf::Color(3, 169, 252));
        finalScore1.setString("PLAYER 1: " + player1Score);
        finalScore1.setPosition({400, 300});

        sf::Text finalScore2;
        finalScore2.setFont(finalScoresFont);
        finalScore2.setCharacterSize(30);
        finalScore2.setFillColor(sf::Color(3, 169, 252));
        finalScore2.setString("PLAYER 2: " + player2Score);
        finalScore2.setPosition({430, 300});

        //Creates walls for the left, right and bottom of the tank to visualise the boundaries of the play area.
        sf::RectangleShape tankWallL;
        tankWallL.setFillColor(sf::Color(128, 128, 128));
        tankWallL.setSize(sf::Vector2f(20, 600));
        tankWallL.setPosition(sf::Vector2f(0, 0));

        sf::RectangleShape tankWallR;
        tankWallR.setFillColor(sf::Color(128, 128, 128));
        tankWallR.setSize(sf::Vector2f(20, 600));
        tankWallR.setPosition(sf::Vector2f(780, 0));

        sf::RectangleShape tankBottom;
        tankBottom.setFillColor(sf::Color(128, 128, 128));
        tankBottom.setSize(sf::Vector2f(800, 20));
        tankBottom.setPosition(sf::Vector2f(0, 580));

        window.clear();

        sf::Vector2f foodPosition;

        //Update the snakes position based on the clock
        if (clock.getElapsedTime().asSeconds() > 0.2f) {

            /*RandomlyAddACollectable();*/
            for (Snake* snake : m_snakeVector) {
                snake->Update();
            }

            //Sets the spawn position of the next collectable to be spawned in
            if (rand() % 3 == 0) {
                for (int i = 0; i < 30; i++) {
                    if (!m_collectables[i].GetAlive() && PlaceIsTaken(m_collectables[i].getPosition())) {
                        sf::Vector2f pos;
                        pos.x = (rand() % ((m_screenWidth - 20) / (int)Snake::m_headSize)) * Snake::m_headSize + 20;
                        pos.y = (rand() % ((m_screenHeight - 20) / (int)Snake::m_headSize)) * Snake::m_headSize + 20;
                        m_collectables[i].Spawn(pos);
                        /*snake.SetGrowth(m_collectables[i].Collision(snake.GetPosition()));*/
                        //m_collectables[i].Render(window);
                        break;
                    }
                }
            }

            CheckCollectablesAboveWater(water.getPosition());

            /*sf::SoundBuffer pickupBuffer;
            pickupBuffer.loadFromFile("Data/SoundFX/pickup_0.wav");
            sf::Sound pickupSound;
            pickupSound.setBuffer(pickupBuffer);*/

            //Draws the next collectable to be spawned in to the window. Also calls the Collision function to check is a snake has eaten it
            for (int i = 0; i < 30; i++) {
                if (m_collectables[i].GetAlive()) {
                    for (Snake* snake : m_snakeVector) {
                        int growBy = m_collectables[i].Collision(snake->GetPosition());
                        if (m_collectables[i].Collision(snake->GetPosition())) {
                            m_collectables[i].setPosition();
                            /*pickupSound.play();*/
                            if (snake == m_snakeVector[0]) {
                                player1Score = player1Score + (growBy * 10);
                            }
                            else if (snake == m_snakeVector[1]) {
                                player2Score = player2Score + (growBy * 10);
                            }
                        }
                        //std::cout << growBy << std::endl;
                        if (growBy > 0)
                        {

                        }
                        snake->SetGrowth(growBy);
                    }
                }
            }
            //Restarts the clock after every cycle through the loop
            clock.restart();
        }

        //Gets the elapsed time of a clock for the water to drop the water level every 1 second
        if (waterClock.getElapsedTime().asSeconds() >= 1.0f) {
            currentWaterDrop += waterDropAmount;
            m_waterDimensions.y -= waterDropAmount;
            water.setSize(m_waterDimensions);
            water.setPosition(Snake::m_headSize, Snake::m_headSize + currentWaterDrop);

            //Restarts the clock every time the water level has dropped
            waterClock.restart();
        }

        //A clock for the playesr oxygen which decreases by 4 every second while the snake is underwater
        if (oxygenClock.getElapsedTime().asSeconds() >= 1.0f) {
            for (Snake* snake : m_snakeVector) {
                if (!snake->IsAboveWater(water.getPosition())) {
                    if (snake == m_snakeVector[0]) {
                        oxygenLevel1 = oxygenLevel1 - 4;
                    }
                    else if (snake == m_snakeVector[1]) {
                        oxygenLevel2 = oxygenLevel2 - 4;
                    }

                    oxygenClock.restart();
                }
                //If the snake is above the water level the oxygen is regained
                else if (snake->IsAboveWater(water.getPosition())) {
                    if (snake == m_snakeVector[0]) {
                        oxygenLevel1 = 100;
                    }
                    else if (snake == m_snakeVector[1]) {
                        oxygenLevel2 = 100;
                    }
                    if (oxygenClock.getElapsedTime().asSeconds() >= 3.0f) {
                        if (player1Score > player2Score) {
                            winnerSnake = "Player 1";
                        }
                        else {
                            winnerSnake = "Player 2";
                        }
                        deathReason = "above water too long";
                        window.clear();
                        window.draw(gameOver);
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            oxygenLevel1 = 100;
        }

        //Draws the water to the window
        window.draw(water);

        //Draws the players score and oxygen level to the window
        window.draw(player1ScoreText);
        window.draw(player2ScoreText);
        

        //Calls the render function of the snake to draw it to the window
        for (Snake* snake : m_snakeVector) {
            snake->Render(window);
        }

        //Draws collectables to the window if they are alive and have a spawn position
        for (int i = 0; i < 30; i++) {
            if (m_collectables[i].GetAlive()) {
                m_collectables[i].Render(window);
            }
        }
        
        //Checks the snake's collisions
        for (Snake* snake : m_snakeVector) {
            if (snake->Collision() == true) {
                /*deathReason = "collision with wall";*/
                window.clear();
                window.draw(gameOver);
            }

            if (snake->SelfCollision() == true) {
                /*deathReason = "self collision";*/
                window.clear();
                window.draw(gameOver);
            }

            //Checks if the snake has oxygen left and kills it if not
            if (!snake->HasOxygenLeft(oxygenLevel1) || !snake->HasOxygenLeft(oxygenLevel2)) {
                /*deathReason = "suffocation";*/
                window.clear();
                window.draw(gameOver);
            }
        }

        if (m_snakeVector[0]->GetPosition() == m_snakeVector[1]->GetPosition()) {
            /*deathReason = "head on collision";*/
            window.clear();
            window.draw(gameOver);
            /*window.draw(finalScore1);
            window.draw(finalScore2);*/
        }
        
        //Draw the walls of the tank to the window
        window.draw(tankWallL);
        window.draw(tankWallR);
        window.draw(tankBottom);

        //Closes the window if the Escape key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.clear();
            window.draw(gameOver);
            window.close();
        }

        // Get the window to display its contents
        window.display();
        counter++;

        //Uses a clock and a counter to calculate the frames per second
        if (clock.getElapsedTime().asSeconds() >= 1.0f) {
            fps = counter;
            counter = 0;
            clock.restart();
        }
    }

    //Deletes the snakes once out of the loop to help save memory and not overflow
    for (Snake* snake : m_snakeVector) {
        delete snake;
    }

    std::cout << "SnakeGame: Finished" << std::endl;
}
