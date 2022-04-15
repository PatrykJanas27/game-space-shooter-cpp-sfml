#pragma once
#include "SFML/Graphics.hpp"

#define Max_NB_ItemsP 4
class menupoz
{
public:
	menupoz(float width, float height);
	~menupoz();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItem; }

private:
	int selectedItem;
	sf::Font font;
	sf::Text menuitems[Max_NB_ItemsP];
};
