#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#define Max_NB_Items 11
class strzelcy
{
public:
	strzelcy(float width, float height);
	~strzelcy();

	void draw(sf::RenderWindow& window);
	int GetPressedItem() { return selectedItem; }
	std::string linia;
	std::string uzytkownik, wynik;

private:
	int selectedItem;
	sf::Font font;
	sf::Text menuitems[Max_NB_Items];
};
