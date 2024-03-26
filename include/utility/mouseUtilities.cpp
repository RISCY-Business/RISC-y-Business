#include "mouseUtilities.h"

MouseUtilities::MouseUtilities()
{
}

bool MouseUtilities::isPointInRectangle(sf::Vector2f POINT, sf::Vector2f CENTER, sf::Vector2f SIZE)
{
    return (POINT.x >= CENTER.x - SIZE.x / 2 && POINT.x <= CENTER.x + SIZE.x / 2 && POINT.y >= CENTER.y - SIZE.y / 2 && POINT.y <= CENTER.y + SIZE.y / 2);
}

bool MouseUtilities::isPointInCircle(sf::Vector2f POINT, sf::Vector2f CENTER, float RADIUS)
{
    return (POINT.x - CENTER.x) * (POINT.x - CENTER.x) + (POINT.y - CENTER.y) * (POINT.y - CENTER.y) <= RADIUS * RADIUS;
}

bool MouseUtilities::isMousePressedInRectangle(sf::Vector2f CENTER, sf::Vector2f SIZE, sf::Event* EVENT)
{
    return EVENT->type == sf::Event::MouseButtonPressed && EVENT->mouseButton.button == sf::Mouse::Left && isPointInRectangle(sf::Vector2f(EVENT->mouseButton.x, EVENT->mouseButton.y), CENTER, SIZE);
}

bool MouseUtilities::isMousePressedInCircle(sf::Vector2f CENTER, float RADIUS, sf::Event* EVENT)
{
    return EVENT->type == sf::Event::MouseButtonPressed && EVENT->mouseButton.button == sf::Mouse::Left && isPointInCircle(sf::Vector2f(EVENT->mouseButton.x, EVENT->mouseButton.y), CENTER, RADIUS);
}

bool MouseUtilities::isMouseInRectangle(sf::Vector2f CENTER, sf::Vector2f SIZE, sf::RenderWindow* WINDOW)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*WINDOW);
    return isPointInRectangle(sf::Vector2f(mousePosition), CENTER, SIZE);
}

bool MouseUtilities::isMouseInCircle(sf::Vector2f CENTER, float RADIUS, sf::RenderWindow* WINDOW)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*WINDOW);
    return isPointInCircle(sf::Vector2f(mousePosition), CENTER, RADIUS);
}

