#include "menu.h"

menu::menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf")) {

	}

	menuitems[0].setFont(font);
	menuitems[0].setFillColor(sf::Color::Red);
	menuitems[0].setStyle(sf::Text::Style::Bold);
	menuitems[0].setString("New Game");
	menuitems[0].setPosition(sf::Vector2f(width / 2.25, height / (Max_NB_Items + 1) * 1));

	menuitems[1].setFont(font);
	menuitems[1].setFillColor(sf::Color::White);
	menuitems[0].setStyle(sf::Text::Style::Bold);
	menuitems[1].setString("Best Players");
	menuitems[1].setPosition(sf::Vector2f(width / 2.28, height / (Max_NB_Items + 1) * 2));

	menuitems[2].setFont(font);
	menuitems[2].setFillColor(sf::Color::White);
	menuitems[0].setStyle(sf::Text::Style::Bold);
	menuitems[2].setString("Quit");
	menuitems[2].setPosition(sf::Vector2f(width / 2.1, height / (Max_NB_Items + 1) * 3));


	selectedItem = 0;
}

menu::~menu()
{
}

void menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_NB_Items; i++) {
		window.draw(menuitems[i]);
	}
}

void menu::MoveUp() {
	if (selectedItem - 1 >= 0) {
		menuitems[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menuitems[selectedItem].setFillColor(sf::Color::Red);
	}
}
void menu::MoveDown() {
	if (selectedItem + 1 < Max_NB_Items) {
		menuitems[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menuitems[selectedItem].setFillColor(sf::Color::Red);
	}
}