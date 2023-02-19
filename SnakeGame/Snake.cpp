#include "Snake.h"
#include <iostream>
#include <vector>
#include <algorithm>

float Snake::m_headSize{ 20.0f };
sf::CircleShape snakeHead;

Snake::Snake(sf::Vector2f pos, sf::Color colour)
{
	m_segmentList.push_back(pos);
	m_colour = colour;
}

//Function to render the snake
void Snake::Render(sf::RenderWindow& window)
{
	//Set the snake's radius(size), colour, and starting position
	sf::CircleShape snake(Snake::m_headSize / 2.0f);
	snake.setFillColor(m_colour);
	snake.setOutlineThickness(1.0f);
	snakeHead = snake;

	for (auto& segment : m_segmentList) {
		snake.setPosition(segment);

		//Draw the snake to the window
		window.draw(snake);
	}

}

//Function for the snakes movement
void Snake::Move()
{
	//Gets the current position of the snake on the screen
	sf::Vector2f currentPos = m_segmentList.front();

	//Check which direction has been stored by key presses, and sets the movement direction accordingly
	switch (m_direction)
	{
	case Direction::North:
		currentPos.y -= Snake::m_headSize;
		break;
	case Direction::East:
		currentPos.x += Snake::m_headSize;
		break;
	case Direction::South:
		currentPos.y += Snake::m_headSize;
		break;
	case Direction::West:
		currentPos.x -= Snake::m_headSize;
		break;
	default:
		break;
	}

	m_segmentList.push_front(currentPos);

	//Pops from the back of the list of snake segments if the snake isn't growing, and adds to the back of the segment list if the snake is growing, 
	//to simulate the tail of the snake following the head
	if (m_growAmount == 0) {
		m_segmentList.pop_back();
	}
	else {
		m_growAmount--;
	}
}

//Function for detecting the snakes collisions with the walls
bool Snake::Collision()
{
	//Gets the current position of the snake
	sf::Vector2f snakePos = m_segmentList.front();

	//Checks the position of the snake to see if it is colliding with the walls
	if (snakePos.x <= 0 || snakePos.x >= 780) {
		return true;
	}
	else if(snakePos.y <= 0 || snakePos.y >= 575) {
		return true;
	}
	else {
		return false;
	}

	if (m_segmentList.size() > 1) {
		if (snakePos == m_segmentList.back()) {
			return true;
		}
	}
}

//Function for detecting the snakes collisions with itself
bool Snake::SelfCollision()
{
	/*sf::Vector2f segment;
	bool isSegment = (std::find(m_segmentList.begin(), m_segmentList.end(), segment) != m_segmentList.end());*/


	
	/*std::vector<sf::Vector2f> m_segementVect;
	for (sf::Vector2f const& segment : m_segmentList) {
		m_segementVect.push_back(segment);
	}
	for (int i = 0; i < m_segementVect.size(); i++) {
		if (m_segementVect[i+1] == m_segmentList.front()) {
			return true;
		}
	}*/
	return false;
}

sf::Vector2f Snake::GetPosition()
{
	//Gets the current position of the snake's head and returns it
	return sf::Vector2f(m_segmentList.front());
}

void Snake::SetGrowth(int growth)
{
	//Sets the growth amount of the snake
	m_growAmount = m_growAmount + growth;
}

int Snake::SetScore()
{
	return 10;
}

bool Snake::DoesCoverPlace(sf::Vector2f pos) const
{
	for (const sf::Vector2f& p : m_segmentList) {
		if (p == pos) {
			return true;
		}
	}

	return false;
}

bool Snake::HasOxygenLeft(int o2)
{
	if (o2 > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Snake::IsAboveWater(sf::Vector2f pos)
{
	sf::Vector2f snakePos = m_segmentList.front();

	if (snakePos.y < pos.y) {
		return true;
	}
	else {
		return false;
	}
}


