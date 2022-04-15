#include "strzelcy.h"

strzelcy::strzelcy(float width, float height) {
	int i = 0, tempvalue;
	int numer = 1, wynik, iloscwierszy = 0;
	std::string wyraz;
	sf::Text* tabstrzelcy = new sf::Text[10];
	sf::Text templogin;
	std::fstream odczyt("ranking.txt");
	if (odczyt.is_open()) {
		while (std::getline(odczyt, linia)) { //dopóki jest co czytac

			iloscwierszy++;
		}
	}
	else {
		std::cout << "Nie udalo odczytac sie pliku!";
	}
	odczyt.close();

	sf::Text tabforlogin[100];
	int tabforvalues[100];

	std::fstream odczyt2("ranking.txt");
	if (odczyt2.is_open()) {
		i = 0;
		while (std::getline(odczyt2, linia)) { //dopóki jest co czytac

			tabforlogin[i].setString(linia.substr(0, linia.length() - 5));
			tabforvalues[i] = atoi((linia.substr(linia.length() - 4, linia.length())).c_str());
			i++;
		}
	}
	else {
		std::cout << "Nie udalo odczytac sie pliku!";
	}
	odczyt2.close();

	for (int j = 0; j < iloscwierszy; j++) {
		for (int z = 1; z < iloscwierszy ; z++) {
			if (tabforvalues[z - 1] < tabforvalues[z]) {
				tempvalue = tabforvalues[z - 1];
				tabforvalues[z - 1] = tabforvalues[z];
				tabforvalues[z] = tempvalue;

				templogin = tabforlogin[z - 1];
				tabforlogin[z - 1] = tabforlogin[z];
				tabforlogin[z] = templogin;
			}
		}
	}

	std::fstream odczyt3("ranking.txt");
	if (odczyt3.is_open()) {
		i = 0;
		while (std::getline(odczyt3, linia)) { //dopóki jest co czytaæ

			wyraz = std::to_string(i + 1);
			wyraz += ". ";
			wyraz += tabforlogin[i].getString() + " " + std::to_string(tabforvalues[i]);
			tabstrzelcy[i].setString(wyraz);
			i++;
			//if (i % 2) { std::cout << std::endl; } //nowa linia co dwa czytane slowa/wyrazy
			if (i == 10)break;
		}
	}
	else {
		std::cout << "Nie udalo odczytac sie pliku!";
	}
	odczyt3.close();
	if (!font.loadFromFile("arial.ttf")) {

	}

	for (int i = 0; i < 10; i++) {
		menuitems[i].setFont(font);
		menuitems[i].setFillColor(sf::Color::White);
		menuitems[i].setCharacterSize(26);
		menuitems[0].setFillColor(sf::Color::Yellow);
		menuitems[1].setFillColor(sf::Color(192, 192, 192));
		menuitems[2].setFillColor(sf::Color(150, 75, 0));
		menuitems[i].setStyle(sf::Text::Style::Bold);
		menuitems[i].setString(tabstrzelcy[i].getString());
		menuitems[i].setPosition(sf::Vector2f(width / 2.3, height / (Max_NB_Items + 1) * (i + 1)));
	}

	menuitems[10].setFont(font);
	menuitems[10].setFillColor(sf::Color::Red);
	menuitems[10].setStyle(sf::Text::Style::Bold);
	menuitems[10].setString("Back");
	menuitems[10].setPosition(sf::Vector2f(width / 2.3, height / (Max_NB_Items + 1) * 11));

	selectedItem = 0;
}

strzelcy::~strzelcy()
{
}

void strzelcy::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_NB_Items; i++) {
		window.draw(menuitems[i]);
	}
}