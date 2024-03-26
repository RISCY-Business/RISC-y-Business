#include <SFML/Graphics.hpp>

class MouseUtilities
{
public:
    MouseUtilities();

    static bool isPointInRectangle(sf::Vector2f POINT, sf::Vector2f CENTER, sf::Vector2f SIZE);
    static bool isPointInCircle(sf::Vector2f POINT, sf::Vector2f CENTER, float RADIUS);

    static bool isMouseInRectangle(sf::Vector2f CENTER, sf::Vector2f SIZE, sf::RenderWindow* WINDOW);
    static bool isMouseInCircle(sf::Vector2f CENTER, float RADIUS, sf::RenderWindow* WINDOW);

    static bool isMousePressedInRectangle(sf::Vector2f CENTER, sf::Vector2f SIZE, sf::Event* EVENT);
    static bool isMousePressedInCircle(sf::Vector2f CENTER, float RADIUS, sf::Event* EVENT);
};
