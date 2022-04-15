#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <string>

#include "menu.h"
#include "menupoz.h"
#include "strzelcy.h"
#include "endgame.h"

using namespace std;
using namespace sf;
int k = 0, usercount = 1, czyjest = 1;
int HP = 120;
int wheels_i = 0;
int pociski_j = 0, key = 0;
int score = 0;
int czestoscmet, czestoscpoc;
bool pokazlogowanie = 1, pokazstrzelcow = 0, pokazgre = 0, pokazmenupoz = 0, pokazglownemenu = 0, pokazkoniecgry = 0, czytrudny = 0, czylatwy = 0, pomin = 0, nowyuser=0;
string user, linia, wyraz, haslo, scorebffile, userlok;

void menu_logowania();


void stop() {
    cout << "\nKoniec programu\n";
    exit(1);
}

void logowanie() {
    bool logingood = 0;
    while (logingood == 0) {
        cout << "\nZaloguj sie \n";
        cout << "->> Podaj nazwe uzytkownika: ";
        cin >> user;
        cout << "->> " << user << " podaj haslo: ";
        cin >> haslo;

        ///////////////////////////////odszyfrowanie hasla
        cout << "->> " << user << " podaj klucz do hasla: ";
        cin >> key;
        
        for (int i = 0; i < haslo.length(); i++) {
            haslo[i] += key;
        }
        //cout << endl << "odszyfrowane haslo: " << haslo;
        ///////////////////////////////////////////////////////

        
        std::ifstream odczyt("konta.txt");
        if (odczyt.is_open()) {
            //cout << "plik otwarty\n";
            int i = 0;
            char wyraz[100];
            string p1;
            string p2;
            while ((odczyt >> wyraz) && i < 100) { //dopóki jest co czytać
                //cout << wyraz << " ";
                if (i % 2 == 0) {
                    p1 = wyraz;
                }
                if (i % 2 == 1) {
                    p2 = wyraz;
                }
                if (p1 == user && p2 == haslo) {
                    logingood = 1;
                }

                i++;
            }
        }
        else {
            cout << "Nie udalo odczyta sie pliku!";
        }
        if (logingood == 0) {
            cout << "Bledne dane logowania\n\n";
            odczyt.close(); //zamknięcie pliku
            menu_logowania();
        }
        
    }
    //cout << "\nPlik zamkniety\n";
    usercount--;
    pokazlogowanie = 0;
    pokazglownemenu = 1;

}



void rejestracja() {
    cout << "Tworzenie nowego konta ";

    std::string linialok, wyrazlok[100];
    std::ifstream odczytk("konta.txt");
    int usercountlok = 1, i = 0;
    while (usercountlok > 0) {
        cout << "\nWpisz swoja nazwe uzytkownika: ";
        cin >> userlok;
        if (odczytk.is_open()) {
            //std::string p1;
            i = 0;
            while (getline(odczytk, linialok)) { //dopóki jest co czytać

                //cout << wyraz << endl;
                wyrazlok[i] = linialok;
                //cout << wyrazlok<<endl;
                
                i++;
            }
            for (i = 0; i < 100; i++) {
                if (wyrazlok[i].substr(0, userlok.length()) == userlok)usercountlok++;
            }

        }
        else {
            cout << "nie udalo sie odczytac pliku";
        }
        if (usercountlok == 1) {
            cout << "->> " << userlok << " podaj haslo: ";
            cin >> haslo;
            ///////////////////szyfrowanie
            cout << "->> " << user << "Podaj klucz do szyfrowania hasla: ";
            cin >> key;
            for (int i = 0; i < haslo.length(); i++) {
                haslo[i] += key;
            }
            /////////////////
            nowyuser = 1;
            break;
        }
        cout << "Taki Uzytkownik juz istnieje\n ";
        usercountlok = 1;
    }
    
    pokazlogowanie = 0;
    pokazglownemenu = 1;
    odczytk.close();
}



void menu_logowania() {
    int w = 0;
    cout << "MENU\n1. Zaloguj sie\n2. Nowy uzytkownik\n3. Pomin\n0. Wyjdz\nWybierz: ";
    cin >> w;
    cout << endl;
    switch (w) {
    case 0:
        stop();
        break;
    case 1:
        logowanie();
        break;
    case 2:
        rejestracja();
        break;
    case 3:
        pomin = 1;
        pokazlogowanie = 0;
        pokazglownemenu = 1;
        break;
    default:
        stop();
        break;

    }
}



int main() {
    menu_logowania();

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Space Shooter");

    //////////////////////////////////////////////////////////////////////////////////////////Definicje/////////////////////////////////////////////////////////////////////////////////////////////// 

    RectangleShape player(Vector2f(150.0f, 150.0f));//okreslenie wielkosci statku
    //player.setFillColor(Color::Red);//ustawia kolor statku

    RectangleShape pocisk(Vector2f(25.0f, 25.0f));//okreslenie wielkosci pocisku
    //pocisk.setFillColor(Color::Green);

    CircleShape circle;//zdefiniowanie kuli/meteoru
    circle.setRadius(25.0f);//promien kuli
    circle.setFillColor(Color::White);//ustawia kolor kulki

    vector<CircleShape> wheels;//tablica dla meteorow, dzieki takiemu zabiegowi mozna renderowac wiele ksztaltow tego samego typu
    vector<RectangleShape> pociski;

    //////////////////////////////////////////////////////////////////////////////////////grafika/textury///////////////////////////////////////////////////////////////////////////////////////////////
    sf::Texture playerTexture;
    playerTexture.loadFromFile("sentinel.png");
    player.setTexture(&playerTexture);

    sf::Texture pociskTexture;
    pociskTexture.loadFromFile("pocisk.png");
    pocisk.setTexture(&pociskTexture);

    sf::Texture wheelsTexture;
    wheelsTexture.loadFromFile("wheels.png");
    circle.setTexture(&wheelsTexture);

    sf::Texture background;
    background.loadFromFile("background.jpg");
    sf::Sprite bg(background);

    sf::Texture background01; //tlo do latwego poziomu
    background01.loadFromFile("background01.jpg");
    sf::Sprite bg01(background01);

    sf::Texture background03; //tlo do trudnego poziomu
    background03.loadFromFile("background03.jpg");
    sf::Sprite bg03(background03);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Create a text
    sf::Text scorevalue("", font);
    scorevalue.setCharacterSize(16);
    scorevalue.setStyle(sf::Text::Bold);
    scorevalue.setFillColor(sf::Color::White);
    scorevalue.setOrigin(0, 0);
    scorevalue.setPosition(75.0f, 0.0f);
    // Draw it (text)

    sf::Text scoretext("Score:", font);
    scoretext.setCharacterSize(16);
    scoretext.setStyle(sf::Text::Bold);
    scoretext.setFillColor(sf::Color::White);
    scoretext.setOrigin(0, 0);
    scoretext.setPosition(0.0f, 0.0f);

    sf::Text HPtext("HP:", font);
    HPtext.setCharacterSize(16);
    HPtext.setStyle(sf::Text::Bold);
    HPtext.setFillColor(sf::Color::White);
    HPtext.setOrigin(0, 0);
    HPtext.setPosition(120.0f, 0.0f);

    sf::Text HPvalue("HP:", font);
    HPvalue.setCharacterSize(16);
    HPvalue.setStyle(sf::Text::Bold);
    HPvalue.setFillColor(sf::Color::White);
    HPvalue.setOrigin(0, 0);
    HPvalue.setPosition(150.0f, 0.0f);


    menu menu(window.getSize().x, window.getSize().y);
    menupoz menupoz(window.getSize().x, window.getSize().y);
    strzelcy strzelcy(window.getSize().x, window.getSize().y);
    endgame endgame(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {

        ///////////////////////////////////////////////////////////////////Glowne menu/////////////////////////////////////////////////////
        if (pokazglownemenu == 1) {

            ////////////////////////////////////////////Tlo glownego menu
            sf::Texture blackbackground;
            blackbackground.loadFromFile("blackbackground.jpg");
            sf::Sprite bbg(blackbackground);
            window.draw(bbg);
            sf::Event evnt;
            /////////////////////////////////////////// Naglowek w glownym menu
            // Declare and load a font
            sf::Font font;
            font.loadFromFile("arial.ttf");
            // Create a text
            sf::Text text("Space Shooter", font);
            text.setCharacterSize(36);
            text.setStyle(sf::Text::Bold);
            text.setOutlineColor(::sf::Color::Blue);
            text.setOutlineThickness(0.2);
            text.setFillColor(sf::Color::Red);
            text.setOrigin(0, 0);
            text.setPosition(480.0f, 20.0f);
            // Draw it (text)
            window.draw(text);

            ////////////////////////////////////////////obsluga glownego menu
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Up: //klikniecie strzalkami do gory
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down: //klikniecie strzalkami w dol
                        menu.MoveDown();
                        break;

                    case sf::Keyboard::Return: //klikniecie ENTER
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            std::cout << "Grasz!" << std::endl;
                            pokazmenupoz = 1; //menu poziom
                            pokazglownemenu = 0;
                            break;

                        case 1:
                            std::cout << "Gracze!" << std::endl;
                            pokazstrzelcow = 1; //ranking graczy
                            pokazglownemenu = 0;
                            break;
                        case 2:
                            window.close(); //Wyjscie z glownego menu/z gry
                            break;
                        }
                        break;
                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }

            menu.draw(window);
            window.display();
        }
        ///////////////////////////////////////////////////////////////////Poziomy Trudnosci///////////////////////////////////////////////
        if (pokazmenupoz == 1) {
            /////////////////////////////////////ustawia tlo menu poziomow
            sf::Texture blackbackground;
            blackbackground.loadFromFile("backgroundpoziom.jpg");
            sf::Sprite bbg(blackbackground);
            window.draw(bbg);
            sf::Event evnt;
            /////////////////////////////////////////// Naglowek w menu poziomow
            // Declare and load a font
            sf::Font font;
            font.loadFromFile("arial.ttf");
            // Create a text
            sf::Text text("Select your level", font);
            text.setCharacterSize(36);
            text.setStyle(sf::Text::Bold);
            text.setFillColor(sf::Color::Red);
            text.setOrigin(0, 0);
            text.setPosition(480.0f, 20.0f);
            // Draw it (text)
            window.draw(text);

            ////////////////////////////////////////////obsluga menu poziomow
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code) {
                    case sf::Keyboard::Up:
                        menupoz.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menupoz.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (menupoz.GetPressedItem())
                        {
                        case 0:
                            std::cout << "latwy" << std::endl;
                            pokazgre = 1;
                            pokazmenupoz = 0;
                            czylatwy = 1;

                            czestoscmet = 1200;
                            czestoscpoc = 400;
                            break;
                        case 1:
                            std::cout << "normalny" << std::endl;
                            pokazgre = 1;
                            pokazmenupoz = 0;

                            czestoscmet = 1000;
                            czestoscpoc = 500;
                            break;
                        case 2:
                            std::cout << "trudny" << std::endl;
                            pokazgre = 1;
                            pokazmenupoz = 0;
                            czytrudny = 1;
                            czestoscmet = 800;
                            czestoscpoc = 600;
                            break;
                        case 3:
                            std::cout << "powrot" << std::endl;
                            pokazglownemenu = 1;
                            pokazgre = 0;
                            pokazmenupoz = 0;
                            czytrudny = 0;
                            break;
                        }
                        break;
                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }

            menupoz.draw(window);

            window.display();
        }
        ///////////////////////////////////////////////////////////////////Najlepsi gracze///////////////////////////////////////////////
        if (pokazstrzelcow == 1) {
            //////////////////////////////ustawia tlo pokazstrzelcow
            sf::Texture blackbackground;
            blackbackground.loadFromFile("backgroundgraczy.jpg");
            sf::Sprite bbg(blackbackground);
            window.draw(bbg);
            sf::Event evnt;
            /////////////////////////////////////////// Naglowek w menu strzelcow
            // Declare and load a font
            sf::Font font;
            font.loadFromFile("arial.ttf");
            // Create a text
            sf::Text text("Best Players", font);
            text.setCharacterSize(32);
            text.setStyle(sf::Text::Bold);
            text.setFillColor(sf::Color::Black);
            text.setOrigin(0, 0);
            text.setPosition(200.0f, 180.0f);
            // Draw it (text)
            window.draw(text);

            while (window.pollEvent(evnt))
            {
                switch (evnt.type) {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code) {
                    case sf::Keyboard::Return:
                        switch (strzelcy.GetPressedItem())
                        {
                        case 0:
                            std::cout << "ok" << std::endl;
                            pokazstrzelcow = 0;
                            pokazglownemenu = 1;

                            break;
                        }
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }

            strzelcy.draw(window);

            window.display();
        }

        ////////////////////////////////////////////////////////////////////////GRA////////////////////////////////////////////////////////
        if (pokazgre == 1) {
            scorevalue.setString(to_string(score));
            HPvalue.setString(to_string(HP));
            //window.clear(Color::Black);//czysci i zamalowuje okno na czarno
            window.draw(bg); //ustawia tlo jpg
            if (czytrudny == 1) {
                window.draw(bg03); //ustawia tlo dla trudnego poziomu
            }
            if (czylatwy == 1) {
                window.draw(bg01); //ustawia tlo dla trudnego poziomu
            }

            //////////////////////////////////////////////////////////////////////////////interakcja z okienkiem///////////////////////////
            Event evnt;
            while (window.pollEvent(evnt))//pollEvent zbiera wszystkie zdarzenia dzia�ajace na okienko
            {
                switch (evnt.type) {
                case Event::Closed:
                    window.close();//przy nacisnieciu x na pasku program sie zamknie
                    break;
                case Event::Resized:
                    cout << "nowy rozmiar szerokosci:" << evnt.size.width << "nowy rozmiar wysokosci:" << evnt.size.height << endl;//za kazda zmiane w rozdzielczosci napisze w terminalu nowe parametry rozdzielczosci
                    break;
                case Event::TextEntered:
                    if (evnt.text.unicode < 128)cout << char(evnt.text.unicode);//wypisze w terminalu wprowadzone z klawiatury znaki bez char() wypisze wartosci ascii
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////Sterowanie//////////////////////////////////////////
            if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
                if (player.getPosition().y < 0.0f)player.setPosition(player.getPosition().x, 0.0f);//uzalezniony od zmiany wysokosci - z gory
                player.move(0.0f, -0.3f);//poruszanie w gore
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
                if (player.getPosition().y > 500.0f)player.setPosition(player.getPosition().x, 500.0f);//uzalezniony od zmiany wysokosci - z dolu
                player.move(0.0f, 0.3f);//poruszanie w dol
            }
            //poruszanie sie prawo/lewo
            if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
                if (player.getPosition().x > 1100.0f)player.setPosition(1100.0f, player.getPosition().y);//uzalezniony od zmiany szerokosci - z prawej strony
                player.move(0.3f, 0.0f);//poruszanie w prawo
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
                if (player.getPosition().x < 0.0f)player.setPosition(0.0f, player.getPosition().y);//(uzalezniony) od zmiany szerkosci - z lewej strony
                player.move(-0.3f, 0.0f);//poruszanie w lewo
            }

            /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


            /// //////////////////////////////////////////////////////////////////////umiejscownienie pocisku i meteoru/////////////////////

            float randomowy_y = rand() % 500 + 30.0f;//szerokosc spawnowania meteorow
            if (czytrudny == 1)
            {
                circle.setPosition(1200.0f, randomowy_y - 50);
            }//poczatkowe wspolrzedne meteoru
            else {
                circle.setPosition(1300.0f, randomowy_y);
            }

            pocisk.setPosition((player.getPosition().x) + 90.0f, (player.getPosition().y) + 70.0f); //uzaleznione od wielkosci statku

            if (k % czestoscmet == 0)wheels.push_back(circle);//co ile klatek ma sie generowac meteor
            if (Keyboard::isKeyPressed(Keyboard::Key::K)) {
                if (k % czestoscpoc == 0)pociski.push_back(pocisk);
            }

            /// //////////////////////////////////////////////////////////////////////////////Zderzenia////////////////////////////////////
            for (size_t i = 0; i < wheels.size(); i++) {//size_t mozna uzywac zamiennie z unsigned int - rozni sie tylko czytelnoscia
                if (czytrudny == 1)wheels[i].move(-0.1f, 0.01f);//poruszanie meteoru w lewa strone
                else {
                    wheels[i].move(-0.1f, 0.0f);
                }
                window.draw(wheels[i]);//rysowanie meteoru
                if (wheels[i].getPosition().x < 0.0f) { //usuwanie meteorow za mapa
                    wheels.erase(wheels.begin() + i);
                    break;
                    window.draw(wheels[i]);
                }
                if (wheels[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
                    //std::cout << "The body have collided";
                    HP -= 37;
                    //std::cout << "Your HP: " << HP << endl;

                    wheels.erase(wheels.begin() + i);
                    //break;
                }
                wheels_i = i;
                for (size_t j = 0; j < pociski.size(); j++) {
                    pociski[j].move(0.2f, 0.0f);//poruszanie w prawo
                    window.draw(pociski[j]);
                    if (pociski[j].getPosition().x > 2400.0f) { //usuwanie pociskow za mapa
                        pociski.erase(pociski.begin() + j);
                        break;
                        window.draw(pociski[j]);
                    }
                    if (pociski[j].getGlobalBounds().intersects(wheels[wheels_i].getGlobalBounds())) {
                        score += 1;
                        //std::cout << "Obiekt zniszczony " << endl;
                        wheels.erase(wheels.begin() + i);

                        pociski.erase(pociski.begin() + j);

                        //std::cout << "Your score: " << score << endl;
                        break;
                        window.draw(wheels[i]);
                        window.draw(pociski[j]);


                    }
                }
            }

            /////////////////////////////////////////////////////////////zapisywanie od pliku dancyh
            if (HP <= 0) {
                pokazgre = 0;
                pokazkoniecgry = 1;

                if (pomin != 1 && nowyuser == 0) {
                    ofstream konta("konta.txt", ios_base::app); // ios_base::app   dopisanie na koncu pliku
                    konta << user << " " << haslo << endl; // korzysta z biblioteki #include<fstream>
                    konta.close();
                    cout << "\nmasz nowe konto";


                    ofstream zapis("ranking.txt", ios_base::app); // ios_base::app   dopisanie na koncu pliku
                    scorebffile = std::to_string(score);
                    if (scorebffile.length() == 1)scorebffile = "000" + scorebffile;
                    if (scorebffile.length() == 2)scorebffile = "00" + scorebffile;
                    if (scorebffile.length() == 3)scorebffile = "0" + scorebffile;
                    zapis << user << " " << scorebffile << endl; // korzysta z biblioteki #include<fstream>
                    zapis.close();
                    cout << "\nTwoj wynik: " << score;
                    cout << "\nZapisywanie do pliku..";
                    ///////tu trzeba dac funkcje zapisujaca login i score do pliku
                }
                if (pomin != 1 && nowyuser == 1) {
                    ofstream konta("konta.txt", ios_base::app); // ios_base::app   dopisanie na koncu pliku
                    konta << userlok << " " << haslo << endl; // korzysta z biblioteki #include<fstream>
                    konta.close();
                    cout << "\nmasz nowe konto";


                    ofstream zapis("ranking.txt", ios_base::app); // ios_base::app   dopisanie na koncu pliku
                    scorebffile = std::to_string(score);
                    if (scorebffile.length() == 1)scorebffile = "000" + scorebffile;
                    if (scorebffile.length() == 2)scorebffile = "00" + scorebffile;
                    if (scorebffile.length() == 3)scorebffile = "0" + scorebffile;
                    zapis << userlok << " " << scorebffile << endl; // korzysta z biblioteki #include<fstream>
                    zapis.close();
                    cout << "\nTwoj wynik: " << score;
                    cout << "\nZapisywanie do pliku..";
                    ///////tu trzeba dac funkcje zapisujaca login i score do pliku
                }
            }



            ////////////////////////////////////////////////////////////////////////////////
            window.draw(player);//rysowanie statku
            //window.draw(wall);
            window.draw(scoretext);
            window.draw(scorevalue);
            window.draw(HPtext);
            window.draw(HPvalue);
            window.display();
            k++;//zmienna potrzebna do rysowania
        }
        ////////////////////////////////////////////////////////////////////////Koniec gry//Zapisywanie danych do pliku////////////////////
        if (pokazkoniecgry == 1) {

            ////////////////////////////////////////////Tlo glownego menu
            sf::Texture blackbackground;
            blackbackground.loadFromFile("blackbackground.jpg");
            sf::Sprite bbg(blackbackground);
            window.draw(bbg);
            sf::Event evnt;
            /////////////////////////////////////////// Naglowek w glownym menu
            // Declare and load a font
            sf::Font font;
            font.loadFromFile("arial.ttf");
            // Create a text
            sf::Text text("Space Shooter", font);
            text.setCharacterSize(36);
            text.setStyle(sf::Text::Bold);
            text.setOutlineColor(::sf::Color::Blue);
            text.setOutlineThickness(0.2);
            text.setFillColor(sf::Color::Red);
            text.setOrigin(0, 0);
            text.setPosition(480.0f, 20.0f);
            // Draw it (text)
            window.draw(text);

            ////////////////////////////////////////////obsluga glownego menu
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Up: //klikniecie strzalkami do gory
                        endgame.MoveUp();
                        break;
                    case sf::Keyboard::Down: //klikniecie strzalkami w dol
                        endgame.MoveDown();
                        break;

                    case sf::Keyboard::Return: //klikniecie ENTER
                        switch (endgame.GetPressedItem())
                        {
                        case 0:
                            break;
                        case 1:
                            window.close(); //Wyjscie z glownego menu/z gry
                            break;
                        }
                        break;
                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }

            endgame.draw(window);
            window.display();
        }


    }
}