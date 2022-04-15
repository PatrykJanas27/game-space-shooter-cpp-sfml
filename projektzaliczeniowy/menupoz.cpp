#include "menupoz.h"


menupoz::menupoz(float width, float height)
{
	if (!font.loadFromFile("arial.ttf")) {

	}

	menuitems[0].setFont(font);
	menuitems[0].setFillColor(sf::Color::Red);
	menuitems[0].setStyle(sf::Text::Style::Bold);
	menuitems[0].setString("Easy");
	menuitems[0].setPosition(sf::Vector2f(width / 2.1, height / (Max_NB_ItemsP + 1) * 1));

	menuitems[1].setFont(font);
	menuitems[1].setFillColor(sf::Color::White);
	menuitems[1].setStyle(sf::Text::Style::Bold);
	menuitems[1].setString("Normal");
	menuitems[1].setPosition(sf::Vector2f(width / 2.1, height / (Max_NB_ItemsP + 1) * 2));

	menuitems[2].setFont(font);
	menuitems[2].setFillColor(sf::Color::White);
	menuitems[2].setStyle(sf::Text::Style::Bold);
	menuitems[2].setString("Hard");
	menuitems[2].setPosition(sf::Vector2f(width / 2.1, height / (Max_NB_ItemsP + 1) * 3));

	menuitems[3].setFont(font);
	menuitems[3].setFillColor(sf::Color::White);
	menuitems[3].setStyle(sf::Text::Style::Bold);
	menuitems[3].setString("Back");
	menuitems[3].setPosition(sf::Vector2f(width / 2.1, height / (Max_NB_ItemsP + 1) * 4));


	selectedItem = 0;
}

menupoz::~menupoz()
{
}

void menupoz::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_NB_ItemsP; i++) {
		window.draw(menuitems[i]);
	}
}

void menupoz::MoveUp() {
	if (selectedItem - 1 >= 0) {
		menuitems[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menuitems[selectedItem].setFillColor(sf::Color::Red);
	}
}
void menupoz::MoveDown() {
	if (selectedItem + 1 < Max_NB_ItemsP) {
		menuitems[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menuitems[selectedItem].setFillColor(sf::Color::Red);
	}
}