#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(sf::Vector2f pos, sf::Color colour,int controls) : Snake(pos, colour), m_controls(controls)
{

}

//Function to update the snake and take input from the user for the movement
void PlayerSnake::Update()
{
	//Movement for player 1 snake (controls 0)
	if (m_controls == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_direction = Direction::North;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_direction = Direction::West;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_direction = Direction::South;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_direction = Direction::East;
		}
	}
	//Movement for player 2 snake (controls 1)
	else if (m_controls == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_direction = Direction::North;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_direction = Direction::West;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_direction = Direction::South;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			m_direction = Direction::East;
		}
	}

	//Calls the move function from the parent class Snake to turn the keyboard inputs into the directions using X and Y coordinates
	Move();
}
