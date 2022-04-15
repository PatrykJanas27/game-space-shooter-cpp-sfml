#pragma once
#include "SFML/Graphics.hpp"

#define Max_NB_Items 3 

class menu
{
public:
	menu(float width, float height);
	~menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItem; }

private:
	int selectedItem;
	sf::Font font;
	sf::Text menuitems[Max_NB_Items];
};