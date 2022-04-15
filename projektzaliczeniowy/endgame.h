#pragma once
#include "SFML/Graphics.hpp"

#define Max_NB_Items 2
class endgame
{
public:
	endgame(float width, float height);
	~endgame();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItem; }

private:
	int selectedItem;
	sf::Font font;
	sf::Text menuitems[Max_NB_Items];
};

