#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include <SFML/Graphics.hpp>
#include "../../../include/utility/soundUtilities.h"
// - - - - - - - - -

class LoadingScreen
{
    public:
        LoadingScreen();
        void run();
    
    private:
        sf::Color backgroundColor = sf::Color(255, 255, 255, 255);
        // - - - - - -  - - -
        std::string textureDirectoryPath = "../../include/resources/textures/";
        std::string fontDirectoryPath = "../../include/resources/fonts/";
        std::string soundDirectoryPath = "../../include/resources/sounds/";
        // - - - - - -  - - -
        sf::Vector2f logoPosition = sf::Vector2f(223, 50);
        sf::Vector2f logoSize = sf::Vector2f(204, 188);
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Text title;
        sf::Font font;
        // - - - - - - -
        sf::RenderWindow window;
        // - - - - - - -
        void update();
        void render();
        void animateTitle(std::string loadingText, unsigned char delay = 100);
        void makeFolder();
        // - - - - - - -
        std::string backspaceSoundFilePath = "backspace.wav";
        std::string typeSoundFilePath = "type.wav";
        SoundUtilities soundEffects;
        
};

#endif // LOADINGSCREEN_H

