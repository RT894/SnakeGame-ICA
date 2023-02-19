#pragma once
#include "Snake.h"
class PlayerSnake :
    public Snake
{
private:
    int m_controls{ 0 };

public:
    PlayerSnake(sf::Vector2f pos, sf::Color colour, int controls);
    void Update() override final;
};

