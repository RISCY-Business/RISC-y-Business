#include "startScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

StartScreen::StartScreen() : clickSound(soundDirectoryPath + clickSoundFilePath, 50)
{
    window.create(sf::VideoMode(1000, 750), "Welcome to RISC-Y Business");
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);

    if (!logoTexture.loadFromFile(textureDirectoryPath + "logo.png"))
    {
        std::cout << "Error loading logo.png" << std::endl;
    }
    logoTexture.setSmooth(true);
    window.setIcon(521, 479, logoTexture.copyToImage().getPixelsPtr());

    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(logoSize.x / logoTexture.getSize().x, logoSize.y / logoTexture.getSize().y);
    logoSprite.setPosition(logoPosition.x, logoPosition.y);

    if (!font.loadFromFile(fontDirectoryPath + "JetBrainsMono-ExtraBold.ttf"))
    {
        std::cout << "Error loading JetBrainsMono-ExtraBold.ttf" << std::endl;
    }
    title.setFont(font);
    title.setString("RISC-Y Business");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Black);
    title.setPosition(logoPosition.x, logoPosition.y + logoSize.y + 20);

    if (!openTexture.loadFromFile(textureDirectoryPath + "open.png"))
    {
        std::cout << "Error loading open.png" << std::endl;
    }
    openTexture.setSmooth(true);
    openSprite.setOrigin(buttonSize.x / 2, buttonSize.y / 2);
    openSprite.setTexture(openTexture);
    openSprite.setPosition(openButtonPosition.x, openButtonPosition.y);

    if (!newTexture.loadFromFile(textureDirectoryPath + "new.png"))
    {
        std::cout << "Error loading new.png" << std::endl;
    }
    newTexture.setSmooth(true);
    newSprite.setTexture(newTexture);
    newSprite.setOrigin(buttonSize.x / 2, buttonSize.y / 2);
    newSprite.setPosition(newButtonPosition.x, newButtonPosition.y);
}

void StartScreen::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}

void StartScreen::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            default:
                break;

            case sf::Event::Closed:
                clickSound.playSoundEffect();
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        if (MouseUtilities::isMouseInRectangle(openButtonPosition, buttonSize, &window))
                        {
                            clickSound.playSoundEffect();
                            std::cout << "Open file" << std::endl;
                        }
                        if (MouseUtilities::isMouseInRectangle(newButtonPosition, buttonSize, &window))
                        {
                            clickSound.playSoundEffect();
                            std::cout << "New file" << std::endl;
                        }
                        break;
                    
                    case sf::Mouse::Right:
                        std::cout << "Right mouse button pressed!" << std::endl;
                        break;
                    default:
                        break;
                }
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::O:
                        std::cout << "Open file" << std::endl;
                        break;
                    case sf::Keyboard::N:
                        std::cout << "New file" << std::endl;
                        break;
                    default:
                        break;
                }
                break;

            case sf::Event::MouseMoved:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (MouseUtilities::isMouseInRectangle(openButtonPosition, buttonSize, &window))
                {
                    while (openSprite.getScale().x < 1.1)
                    {
                        openSprite.setScale(openSprite.getScale().x + 0.0001, openSprite.getScale().y + 0.0001);
                    }
                }
                else
                {
                    while (openSprite.getScale().x > 1)
                    {
                        openSprite.setScale(openSprite.getScale().x - 0.0001, openSprite.getScale().y - 0.0001);
                    }
                }
                if (MouseUtilities::isMouseInRectangle(newButtonPosition, buttonSize, &window))
                {
                    while (newSprite.getScale().x < 1.1)
                    {
                        newSprite.setScale(newSprite.getScale().x + 0.0001, newSprite.getScale().y + 0.0001);
                    }
                }
                else
                {
                    while (newSprite.getScale().x > 1)
                    {
                        newSprite.setScale(newSprite.getScale().x - 0.0001, newSprite.getScale().y - 0.0001);
                    }
                }
                break;
        }
    }
}


void StartScreen::render()
{
    window.clear(sf::Color(239, 239, 239, 255));
    window.draw(logoSprite);
    window.draw(title);
    window.draw(newSprite);
    window.draw(openSprite);
    window.display();
}
