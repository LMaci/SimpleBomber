#ifndef SAPER_H
#define SAPER_H
#include<SFML/Graphics.hpp>

class pole
{
public:
    sf::RectangleShape kwadrat;
    bool odkryte;
    unsigned short ile_obok;
    bool czy_bomba;
    bool flaga;

public:
    pole(sf::Vector2f pozycja)
    {
        kwadrat.setPosition(pozycja);
        kwadrat.setSize(sf::Vector2f(19,19));
        kwadrat.setOutlineThickness(1);
        kwadrat.setOutlineColor(sf::Color::Black);
        odkryte=0;
        ile_obok=0;
        czy_bomba=0;
        flaga=0;
    }
};

#endif
