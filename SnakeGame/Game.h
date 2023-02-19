#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Collectables.h"
#include "Snake.h"

class Game
{
private:
	//Variables to determing the width and height of the window
	int m_screenWidth{ 800 };
	int m_screenHeight{ 600 };

	//A vector to store all of the snakes that will be in play
	std::vector<Snake*> m_snakeVector;

	Collectables m_collectables[30];

	//A vector 2f to store the dimensions of the water
	sf::Vector2f m_waterDimensions;

public:
	void Run();
	bool PlaceIsTaken(sf::Vector2f pos) const;
	void RandomlyAddACollectable();
	void CheckCollectablesAboveWater(sf::Vector2f pos);
	sf::Vector2f FreeSpacePos();
};

