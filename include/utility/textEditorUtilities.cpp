#include "textEditorUtilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

TextEditorUtilities::TextEditorUtilities(sf::RenderWindow* WINDOW, unsigned short WIDTH, unsigned short HEIGHT) : window(WINDOW)
{
	viewWidth = WIDTH;
	viewHeight = HEIGHT;
	font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf");
	colorClock.restart();
	
	scroller.reset(sf::FloatRect(0, 0, viewWidth, viewHeight));

	cursor.setSize(sf::Vector2f(5, size));
	cursor.setFillColor(sf::Color(100, 0, 0, 100));
	
	window->setView(scroller);
}

void TextEditorUtilities::scrollUp()
{
	if (cursorLine <= topDisplayedLine || cursor.getPosition().y > 100)
	{
		return;
	}
	scroller.move(0, textContent[0].getCharacterSize());
	--topDisplayedLine;
	--bottomDisplayedLine;
	if (topDisplayedLine <= 0)
	{
		topDisplayedLine = 0;
	}
	window->setView(scroller);
}

void TextEditorUtilities::scrollDown()
{
	if (cursorLine <= bottomDisplayedLine || cursor.getPosition().y < viewHeight/2)
	{
		return;
	}
	scroller.move(0, -size - linePadding);
	++bottomDisplayedLine;
	++topDisplayedLine;
	if (bottomDisplayedLine > textContent.size() - 1)
	{
		bottomDisplayedLine = textContent.size() - 1;
	}

	window->setView(scroller);
}

void TextEditorUtilities::setCursorPosition()
{
	cursor.setPosition(textContent[cursorLine].getPosition().x + (7 * cursorPos), cursorLine * size + textContent[0].getPosition().y);
}

void TextEditorUtilities::render()
{
	elapsedTime = colorClock.getElapsedTime().asSeconds() * 2;
    float red = (std::sin(elapsedTime + 0) * 127) + 128;
    float green = (std::sin(elapsedTime + 2 * pi / 3) * 127) + 128;
    float blue = (std::sin(elapsedTime + 4 * pi / 3) * 127) + 128;
	textColor = sf::Color(red, green, blue);
	window->setView(scroller);
	window->draw(cursor);
	for (int i = 0; i < textContent.size(); ++i)
	{
		textContent[i].setFillColor(textColor);
		lineNumbers[i].setFillColor(textColor);
		window->draw(textContent[i]);
		window->draw(lineNumbers[i]);
	}
}

void TextEditorUtilities::setFilePath(std::string& PATH)
{
	filePath = PATH;
}

void TextEditorUtilities::readFromFile()
{
	status = "Reading from file" + filePath;
	std::ifstream infile(filePath);
	switch (infile.is_open())
	{
		case true:
			break;
			
		case false:
			std::cerr << "Error opening file to read\n";
			return;
			break;
	}
	
	textContent.clear();
	lineNumbers.clear();
	
	std::string line;
	int i = 2;
	if (infile.peek() == std::ifstream::traits_type::eof()) 
	{
        infile.close();
        return;  // Return if the file is empty
    }
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		sf::Text text;
		sf::Text number;
		text.setFont(font);
		number.setFont(font);
		text.setFillColor(sf::Color::Black);
		number.setFillColor(sf::Color::Black);
		text.setCharacterSize(size);
		number.setCharacterSize(size);
		text.setString(line);
		number.setString(std::to_string(i - 1));
		text.setPosition(sf::Vector2f(80, (i * size) + 60));
		number.setPosition(sf::Vector2f(10, (i * size) + 60));
		++i;
		
		textContent.push_back(text);
		lineNumbers.push_back(number);
	}
	setCursorPosition();	
	topDisplayedLine = 0;
	bottomDisplayedLine = std::min((int)textContent.size() - 1, 25);
	infile.close();	
}
	
void TextEditorUtilities::writeToFile()
{
	status = "writing to file path" + filePath;
	std::ofstream outputFile(filePath);
	switch (outputFile.is_open())
	{
		case true:
			break;
					
		case false:
			std::cerr << "Could not open file for writing" << std::endl;
			break;
	}
				
	for (const auto& lineText : textContent)
	{
		outputFile << lineText.getString().toAnsiString() << "\n";
	}
			
	outputFile.close();
	isEdited = false;
	switch(isEdited)
	{
		case false:
			return;
			break;

		case true:
			break;
	}
	
}	

void TextEditorUtilities::moveCursorUp()
{
	if (cursorLine > 0)
	{
		--cursorLine;
		cursorPos = (cursorPos > textContent[cursorLine].getString().toAnsiString().length()) ? textContent[cursorLine].getString().toAnsiString().length() : cursorPos;
		setCursorPosition();
		return;
	}
}

void TextEditorUtilities::moveCursorDown()
{
	if (cursorLine < textContent.size() - 1)
	{
		++cursorLine;
		cursorPos = (cursorPos > textContent[cursorLine].getString().toAnsiString().length()) ? textContent[cursorLine].getString().toAnsiString().length() : cursorPos;
		setCursorPosition();
		return;
	}
}

void TextEditorUtilities::moveCursorLeft()
{
	if (cursorPos > 0)
	{
		--cursorPos;
		setCursorPosition();
		return;
	}
	if (cursorLine > 0)
	{
		cursorPos = textContent[cursorLine - 1].getString().toAnsiString().length();
	}
	moveCursorUp();
}

void TextEditorUtilities::moveCursorRight()
{
	if (cursorPos < textContent[cursorLine].getString().toAnsiString().length())
	{
		++cursorPos;
		setCursorPosition();
		return;
	}
	if (cursorLine < textContent.size() -1)
	{
		cursorPos = 0;
	}
	moveCursorDown();
}

void TextEditorUtilities::makeANewLine()
{
	sf::Text newLine;
	sf::Text newNumber;
	newLine.setFont(font);
	newNumber.setFont(font);
	newLine.setCharacterSize(size);
	newNumber.setCharacterSize(size);
	newLine.setFillColor(sf::Color::Black);
	newNumber.setFillColor(sf::Color::Black);
	textContent.insert(textContent.begin() + cursorLine + 1, newLine);
	lineNumbers.insert(lineNumbers.begin() + cursorLine + 1, newNumber);

	++cursorLine;
	std::string previousLine = textContent[cursorLine -1].getString().toAnsiString();
	std::string whatGoesBefore  = previousLine.substr(0, cursorPos);
	std::string whatGoesAfter = previousLine.substr(cursorPos);
	textContent[cursorLine - 1].setString(whatGoesBefore);
	textContent[cursorLine].setString(whatGoesAfter);
	cursorPos = 0;
	newNumber.setString("Temporary");
	for (int i = cursorLine; i < textContent.size(); ++i)
	{
		textContent[i].setPosition(sf::Vector2f(80, ((i + 2) * size) + 60));
		lineNumbers[i].setPosition(sf::Vector2f(10, ((i + 2) * size) + 60));
	}
	
	isEdited = true;

	setCursorPosition();
}

void TextEditorUtilities::addACharacter(char C)
{
	sf::Text& line = textContent[cursorLine];
	std::string lineText = line.getString().toAnsiString();
	lineText.insert(cursorPos, 1, C);
	line.setString(lineText);
	++cursorPos;
	setCursorPosition();
}

void TextEditorUtilities::insertChar(char C)
{
	switch(C == '\n')
	{
		case true:
			makeANewLine();
			break;
			
		case false:
			addACharacter(C);
			break;
	}
	
	isEdited = true;
}

void TextEditorUtilities::deleteChar()
{
	sf::Text& line = textContent[cursorLine];
	std::string lineText = line.getString().toAnsiString();
	switch(cursorPos > 0)
	{
		case true:
			lineText.erase(cursorPos -1, 1);
			line.setString(lineText);
			--cursorPos;
			isEdited = true;
			setCursorPosition();
			break;
			
		case false:
			switch(cursorLine > 0)
			{
				case false:
					break;
					
				case true:
					std::string previousLine = textContent[cursorLine -1].getString().toAnsiString();
					cursorPos = previousLine.length();
					previousLine += lineText;
					textContent.erase(textContent.begin() + cursorLine);
					textContent[cursorLine - 1].setString(previousLine);
					--cursorLine;
					for (int i = cursorLine; i < textContent.size(); ++i)
					{
						textContent[i].setPosition(sf::Vector2f(80, ((i + 2) * size) + 60));
					}
					isEdited = true;
					setCursorPosition();
					break;
			}
			break;
	}
}

void TextEditorUtilities::undo()
{
	switch(undoStack.empty()) 
	{
		case true:
			std::cout << "Undo stack is empty!" << std::endl;
			break;

		case false:
            redoStack.push(latest);
            latest = undoStack.top();
            undoStack.pop();

            cursorLine = latest.cursorLine;
            cursorPos = latest.cursorPos;

            int startLine = cursorLine > 2 ? cursorLine - 2 : 0;
            int endLine = cursorLine + 2 < textContent.size() ? cursorLine + 2 : textContent.size() - 1;
            for (int i = startLine; i <= endLine; ++i) 
			{
                textContent[i] = latest.theText[i - startLine];
            }

    }
}

void TextEditorUtilities::redo()
{
	switch(redoStack.empty()) 
	{
		case true:
			std::cout << "Redo stack is empty!" << std::endl;
			break;

		case false:
            latest = redoStack.top();
            redoStack.pop();

            cursorLine = latest.cursorLine;
            cursorPos = latest.cursorPos;

            int startLine = cursorLine > 2 ? cursorLine - 2 : 0;
            int endLine = cursorLine + 2 < textContent.size() ? cursorLine + 2 : textContent.size() - 1;
            for (int i = startLine; i <= endLine; ++i) 
			{
                textContent[i] = latest.theText[i - startLine];
            }

    }
}

void TextEditorUtilities::updateSnapshot()
{
	Snapshot newSnap;
    newSnap.cursorLine = cursorLine;
    newSnap.cursorPos = cursorPos;

    int startLine = cursorLine > 2 ? cursorLine - 2 : 0;
    int endLine = cursorLine + 2 < textContent.size() ? cursorLine + 2 : textContent.size() - 1;
    for (int i = startLine; i <= endLine; ++i) 
	{
		newSnap.theText[i - startLine] = textContent[i];
    }

    latest = newSnap;
}

void TextEditorUtilities::update(const sf::Event* EVENT)
{
	status = "CursorLine" + std::to_string(cursorLine) + "\tCursorPosition" + std::to_string(cursorPos) + "\t\tTotal: " + std::to_string(textContent.size()) + "\n";
	std::cout << status << std::endl;
	std::cout << topDisplayedLine << " " << bottomDisplayedLine << std::endl;
	for (auto i : textContent)
	{
		i.setFillColor(textColor);
	}
	
	switch(abs(previousCursorLine - cursorLine) < 5)
	{
		case true:
			break;
			
		case false:
			previousCursorLine = cursorLine;
			if (lastKeyPress == sf::Keyboard::Down || lastKeyPress == sf::Keyboard::Up || lastKeyPress == sf::Keyboard::Left || lastKeyPress == sf::Keyboard::Right || lastKeyPress == sf::Keyboard::Home || lastKeyPress == sf::Keyboard::End)
			{
				previousCursorLine = cursorLine;
				updateSnapshot();
				undoStack.push(latest);
			}
			break;
	}
	
	switch(specialKeyPressed)
	{
		case true:
			updateSnapshot();
			undoStack.push(latest);
			specialKeyPressed = false;
			break;
			
		case false:
			break;
	}
	
	switch(EVENT->type)
	{
		case sf::Event::TextEntered:
			switch(EVENT->text.unicode >= 32 && EVENT->text.unicode <127)
			{
				case true:
					insertChar(static_cast<char>(EVENT->text.unicode));				
					break;
					
				case false:
					switch(EVENT->text.unicode == '\b')
					{
						case true:
							deleteChar();
							break;
							
						case false:
							break;
					}
					break;
			}
			break;
			
		case sf::Event::KeyPressed:
			switch(EVENT->key.code)
			{
				case sf::Keyboard::Left:
					moveCursorLeft();
					break;
					
				case sf::Keyboard::Right:
					moveCursorRight();
					break;
					
				case sf::Keyboard::Up:
					scrollUp();
					moveCursorUp();
					break;
				
				case sf::Keyboard::Down:
					scrollDown();
					moveCursorDown();
					break;

				case sf::Keyboard::PageUp:
					scrollUp();
					break;

				case sf::Keyboard::PageDown:
					scrollDown();
					break;

				case sf::Keyboard::S:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
						std::cout << "Writing to File" << std::endl;
							writeToFile();
							break;
						
						case false:
							break;
					}
					break;

				case sf::Keyboard::Z:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
							switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
							{
								case true:
									std::cout << "Redo Call detected" <<std::endl;
									redo();
									break;
									
								case false:
									std::cout << "Undo call detected" << std::endl;
									undo();
									break;
							}
							break;
					}
					break;					

				case sf::Keyboard::Return:
					setSpecialKeyPress();
					makeANewLine();
					break;

				case sf::Keyboard::Tab:
					setSpecialKeyPress();
					for (int i = 0; i < 4; ++i)
					{
						insertChar(' ');
					}
					break;

				case sf::Keyboard::Delete:
					setSpecialKeyPress();
					cursorPos++;
					if (cursorPos >= textContent[cursorLine].getString().toAnsiString().length() && textContent.size() - 1 > cursorLine)
					{
						cursorLine++;
						cursorPos = 0;
					}
					deleteChar();
					break;

				case sf::Keyboard::Home:
					cursorPos = 0;
					setCursorPosition();
					break;

				case sf::Keyboard::End:
					cursorPos = textContent[cursorLine].getString().toAnsiString().length();
					setCursorPosition();
					break;
			}
			break;
			
		default:
			break;
	}
}

void TextEditorUtilities::setSpecialKeyPress()
{
	switch(keyClock.getElapsedTime().asSeconds() > 1)
	{
		case true:
			specialKeyPressed = true;
			keyClock.restart();
			break;
			
		case false:
			specialKeyPressed = false;
			break;
	}
	updateSnapshot();
	undoStack.push(latest);
}