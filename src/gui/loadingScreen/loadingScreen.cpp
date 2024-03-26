#include "loadingScreen.h"
#include <filesystem>
#include <iostream>

LoadingScreen::LoadingScreen(): soundEffects(soundDirectoryPath + typeSoundFilePath, 50)
{
    window.create(sf::VideoMode(650, 400), "RISC-Y Business", sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);
    window.clear(backgroundColor);
    window.display();

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
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Black);
    title.setString("RISCY Business");
    title.setPosition((window.getSize().x - title.getGlobalBounds().width) / 2, logoPosition.y + logoSize.y + 50);
}

void LoadingScreen::animateTitle(std::string loadingText, unsigned char delay)
{
    soundEffects.setPath(soundDirectoryPath + typeSoundFilePath);
    sf::sleep(sf::seconds(1));

    soundEffects.playSoundEffect();
    for (unsigned char i = 0; i < loadingText.size(); ++i)
    {
        title.setString(title.getString() + loadingText[i]);
        title.setPosition((window.getSize().x - title.getGlobalBounds().width) / 2, title.getPosition().y);
        render();
        sf::sleep(sf::milliseconds(delay));
    }
    soundEffects.stopSoundEffect();

    sf::sleep(sf::seconds(1));

    soundEffects.setPath(soundDirectoryPath + backspaceSoundFilePath);
    soundEffects.playSoundEffect();
    for (unsigned char i = 0; i < loadingText.size(); ++i)
    {
        title.setString(title.getString().substring(0, title.getString().getSize() - 1));
        render();
        sf::sleep(sf::milliseconds(delay/2));
    }
    soundEffects.stopSoundEffect();
}

void LoadingScreen::run()
{
    render();
    makeFolder();
    sf::sleep(sf::seconds(1));
    title.setString("");
    animateTitle("beq r1, r2, 0x4", 50);
    animateTitle("000100001001100", 50);
    title.setString("Execution Complete");
    title.setPosition((window.getSize().x - title.getGlobalBounds().width) / 2, logoPosition.y + logoSize.y + 50);
    render();
    sf::sleep(sf::seconds(1));
    title.setString("Segmentation Fault");
    title.setPosition((window.getSize().x - title.getGlobalBounds().width) / 2, logoPosition.y + logoSize.y + 50);
    render();
    sf::sleep(sf::seconds(0.01));
    window.close();

}

void LoadingScreen::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;

            default:
                break;
        }
    }
}

void LoadingScreen::render()
{
    window.clear(backgroundColor);
    window.draw(logoSprite);
    window.draw(title);
    window.display();
}

void LoadingScreen::makeFolder()
{
    std::string projectsDirectory = std::getenv("HOME");
    projectsDirectory += "/RISCY Projects";
    if (!std::filesystem::exists(projectsDirectory))
    {
        std::filesystem::create_directory(projectsDirectory);
    }
}
