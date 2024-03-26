#ifndef DIALOG_BOX_H
#define DIALOG_BOX_H

#include <SFML/Graphics.hpp>

class DialogBox {
public:
    DialogBox();
    virtual ~DialogBox();

    void display();

protected:
    sf::RenderWindow window;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::Text titleText;
    sf::Font font;

    virtual void renderContent() = 0;
    virtual void handleEvent(const sf::Event& event);
};

#endif // DIALOG_BOX_H
