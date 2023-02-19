#pragma once
#include <SFML/Graphics.hpp>
#include <list>

//An enumerator class named Direction to set movement direction for the snake
enum class Direction {
	North,
	East,
	South,
	West
};

class Snake
{
	//private variables for each of the snake's attributes
private:
	sf::Color m_colour;
	std::list<sf::Vector2f> m_segmentList;
	int m_growAmount = 0;
	bool m_alive{ true };

protected:
	Direction m_direction = Direction::East;
	void Move();

public:
	static float m_headSize;

	Snake(sf::Vector2f pos, sf::Color colour);

	virtual void Update() = 0;

	void Render(sf::RenderWindow& window);
	bool Collision();
	bool SelfCollision();
	sf::Vector2f GetPosition();
	void SetGrowth(int growth);
	int SetScore();
	bool DoesCoverPlace(sf::Vector2f pos) const;
	bool HasOxygenLeft(int o2);
	bool IsAboveWater(sf::Vector2f pos);
	//void Eat(sf::Vector2f foodPos);

};

