#ifndef TEXTEDITORUTILITIES_H
#define TEXTEDITORUTILITIES_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class TextEditorUtilities
{
	std::string filePath;
	std::vector<sf::Text> textContent;
	std::string textureDirectoryPath = "../../include/resources/textures/";
    std::string fontDirectoryPath = "../../include/resources/fonts/";
    std::string soundDirectoryPath = "../../include/resources/sounds/";
	sf::RenderWindow* window;
	sf::Font font;
	sf::RectangleShape cursor;
	unsigned char cursorLine = 0;
    unsigned char cursorPos = 0;
	sf::View scroller;
	unsigned char size = 12;

	bool showCursor = false;
	
	bool isEdited = false;
	sf::Vector2f viewArea = sf::Vector2f(800, 600);
	int linePadding = 2;

	void insertChar(char C);
	
	void deleteChar();
	
	void scrollUp();
	
	void scrollDown();
	
	void moveCursorRight();
	
	void moveCursorLeft();
	
	void moveCursorDown();
	
	void moveCursorUp();

	void setCursorPosition();

	void addACharacter(char C);

	void makeANewLine();

	void scrollDownLogic();
	
public:
	TextEditorUtilities(sf::RenderWindow* WINDOW);

	void setFilePath(std::string& PATH);
		
	void writeToFile();
	
	void readFromFile();
	
	void update(const sf::Event* EVENT);
	
	void render();
	
	
};

#endif //TEXTEDITORUTILITIES_H
