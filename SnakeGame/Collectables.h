#pragma once
#include <SFML/Graphics.hpp>

class Collectables
{
private:
	sf::Vector2f m_position;
	int m_score{ 0 };
	bool m_alive{ false };

public:
	void Render(sf::RenderWindow& window);
	bool GetAlive() const { return m_alive; }
	int getScore() const { return m_score; }
	void Spawn(sf::Vector2f spawnPos);
	int Collision(sf::Vector2f snakePos);
	sf::Vector2f getPosition() const;
	sf::Vector2f setPosition();
	sf::Vector2f setNewPosition(sf::Vector2f pos);
};	

