#include "endgame.h"

endgame::endgame(float width, float height)
{
	if (!font.loadFromFile("arial.ttf")) {

	}

	menuitems[0].setFont(font);
	menuitems[0].setFillColor(sf::Color::Red);
	menuitems[0].setStyle(sf::Text::Style::Bold);
	menuitems[0].setString("You lose");
	menuitems[0].setPosition(sf::Vector2f(width / 2.5, height / (Max_NB_Items + 1) * 1));
	menuitems[0].setCharacterSize(60);

	

	menuitems[1].setFont(font);
	menuitems[1].setFillColor(sf::Color::White);
	menuitems[0].setStyle(sf::Text::Style::Bold);
	menuitems[1].setString("Quit");
	menuitems[1].setPosition(sf::Vector2f(width / 2.15, height / (Max_NB_Items + 1) * 2));



	selectedItem = 1;
}

endgame::~endgame()
{
}

void endgame::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_NB_Items; i++) {
		window.draw(menuitems[i]);
	}
}

void endgame::MoveUp() {
	if (selectedItem - 1 >= 1) {
		menuitems[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menuitems[selectedItem].setFillColor(sf::Color::Red);
	}
}
void endgame::MoveDown() {
	if (selectedItem + 1 < Max_NB_Items) {
		menuitems[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menuitems[selectedItem].setFillColor(sf::Color::Red);
	}
}