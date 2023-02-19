#include "Collectables.h"
#include <iostream>

void Collectables::Render(sf::RenderWindow& window)
{
	/*sf::Texture collectableTexture;
	collectableTexture.loadFromFile("Data/Textures/8-bit fruit.png");
	sf::Sprite foodSprite;
	foodSprite.setScale(sf::Vector2f(2.0f, 2.0f));
	foodSprite.setPosition(m_position);*/
	//if (!m_alive)
	//{
	//	return;
	//}
	//std::cout << "Render " << m_position.x << " " << m_position.y << std::endl;
	sf::CircleShape food(10.0f);
	food.setPosition(m_position);
	food.setFillColor(sf::Color(0, 255, 0));
	food.setOutlineThickness(3.0f);

	window.draw(food);
}

//Function to spawn the collectables
void Collectables::Spawn(sf::Vector2f spawnPos)
{
	m_score = rand() % 5 + 1;
	m_alive = true;
	m_position = spawnPos;

}

//Function to detect collisions with a snake
int Collectables::Collision(sf::Vector2f snakePos)
{
	if (m_position == snakePos) {
		return 1 + rand() % 3;
	}
	return 0;
}

sf::Vector2f Collectables::getPosition() const
{
	return m_position;
}

sf::Vector2f Collectables::setPosition()
{
	sf::Vector2f offScreen = sf::Vector2f(-2.0f,-2.0f);
	m_position = offScreen;
	return m_position;
}

sf::Vector2f Collectables::setNewPosition(sf::Vector2f pos)
{
	m_position = pos;
	return m_position;
}
