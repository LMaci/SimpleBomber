#include<SFML/Graphics.hpp>
#include"saper.h"
#include<iostream>
#include<cmath>
#include<windows.h>
#include<vector>
#include<cstdlib>
#include<ctime>



void losowanie(unsigned int ile_losowan, std::vector<pole> & wektor)
{
    unsigned zakres_gora=wektor.size();
    unsigned zakres_dol=0;
    int a;
    std::vector<unsigned int> wyniki;

    do
    {
        bool dziala=1;
        a=((rand()%zakres_gora)+zakres_dol);


        for(unsigned int i=0;i<wyniki.size();i++)
            if(a==wyniki[i])
                dziala=0;

            if(dziala)
                wyniki.push_back(a);

    }while(wyniki.size()<ile_losowan);

    for(unsigned int i=0;i<wyniki.size();i++)
        wektor[wyniki[i]].czy_bomba=1;
    wyniki.clear();
}

void podlicza_obok(std::vector<pole> & wektor, unsigned int X)
{
    for(unsigned int i=0;i<wektor.size();i++)
    {
        bool blok_gora=0;
        bool blok_dol=0;
        bool blok_prawo=0;
        bool blok_lewo=0;

        if(wektor[i].czy_bomba==1)
        {
            if((i-X)<0)
                blok_gora=1;
            if((i+X)>wektor.size()-1)
                blok_dol=1;
            if(((i+1)%X)==0)
                blok_prawo=1;
            if((i%X)==0)
                blok_lewo=1;

            //dodaje liczbe boczna;

            if(!blok_lewo)
                wektor[i-1].ile_obok+=1;
            if(!blok_prawo)
                wektor[i+1].ile_obok+=1;
            if(!blok_gora)
            {
                wektor[i-X].ile_obok+=1;

                if(!blok_lewo)
                    wektor[i-(X+1)].ile_obok+=1;
                if(!blok_prawo)
                    wektor[i-(X-1)].ile_obok+=1;
            }

            if(!blok_dol)
            {
                wektor[i+X].ile_obok+=1;

                if(!blok_lewo)
                    wektor[i+(X-1)].ile_obok+=1;
                if(!blok_prawo)
                    wektor[i+(X+1)].ile_obok+=1;
            }
        }
    }
}

void odslanianiepoLPM(std::vector <pole> & wektor, unsigned int X)
{
    bool skoncz=1;
    do
    {
        skoncz=1;

        for(int i=0;i<wektor.size();i++)
        {
            if(wektor[i].odkryte==1 && wektor[i].ile_obok==0)
            {
                bool blok_gora=0;
                bool blok_dol=0;
                bool blok_prawo=0;
                bool blok_lewo=0;

                if((i-X)<0)
                    blok_gora=1;
                if((i+X)>wektor.size()-1)
                    blok_dol=1;
                if(((i+1)%X)==0)
                    blok_prawo=1;
                if((i%X)==0)
                    blok_lewo=1;

                if(!blok_lewo&&wektor[i-1].odkryte==0)
                {
                    wektor[i-1].odkryte=1;
                    skoncz=0;
                }
                if(!blok_prawo&&wektor[i+1].odkryte==0)
                {
                    wektor[i+1].odkryte=1;
                    skoncz=0;
                }
                if(!blok_gora)
                {
                    if(wektor[i-X].odkryte==0)
                    {
                        wektor[i-X].odkryte=1;
                        skoncz=0;
                    }

                    if(!blok_lewo&&wektor[i-(X+1)].odkryte==0)
                    {
                        wektor[i-(X+1)].odkryte=1;
                        skoncz=0;
                    }
                    if(!blok_prawo&&wektor[i-(X-1)].odkryte==0)
                    {
                        wektor[i-(X-1)].odkryte=1;
                        skoncz=0;
                    }
                }

                if(!blok_dol)
                {
                    if(wektor[i+X].odkryte==0)
                    {
                        wektor[i+X].odkryte=1;
                        skoncz=0;
                    }
                    if(!blok_lewo&&wektor[i+(X-1)].odkryte==0)
                    {
                        wektor[i+(X-1)].odkryte=1;
                        skoncz=0;
                    }
                    if(!blok_prawo&&wektor[i+(X+1)].odkryte==0)
                    {
                        wektor[i+(X+1)].odkryte=1;
                        skoncz=0;
                    }
                }
            }
        }
    }while(!skoncz);

}




int main()
{
    srand(time(NULL));
    unsigned int ilosc_bomb=30;
    unsigned short WX=20;//szerokosc jednego pola
    unsigned short WY=20;//wysokosc jednego pola

    unsigned short AllX=20;//wszystkie pola w poziomie
    unsigned short AllY=20;//wszystkie pola w pionie

    bool przegrana=0;


    sf::Texture zakryte;
    zakryte.loadFromFile("dosapera//zakryte.png");
    sf::Texture mina;
    mina.loadFromFile("dosapera//bomba.png");
    sf::Texture flaga;
    flaga.loadFromFile("dosapera//flaga.png");
    sf::Texture liczbowe [9];
    liczbowe[0].loadFromFile("dosapera//0.png");
    liczbowe[1].loadFromFile("dosapera//1.png");
    liczbowe[2].loadFromFile("dosapera//2.png");
    liczbowe[3].loadFromFile("dosapera//3.png");
    liczbowe[4].loadFromFile("dosapera//4.png");
    liczbowe[5].loadFromFile("dosapera//5.png");
    liczbowe[6].loadFromFile("dosapera//6.png");
    liczbowe[7].loadFromFile("dosapera//7.png");
    liczbowe[8].loadFromFile("dosapera//8.png");

    srand(time(NULL));
    sf::ContextSettings ustawienia;
    ustawienia.antialiasingLevel=8;
	sf::RenderWindow okno(sf::VideoMode(400,400,32), "Saper",sf::Style::Default,ustawienia);
    okno.setFramerateLimit(100);

    std::vector<pole> kwadracik;


    for(unsigned short i=0;i<AllY;i++)
        for(unsigned short j=0;j<AllX;j++)
        {
            kwadracik.push_back(pole(sf::Vector2f(j*WX,i*WY)));
        }

    losowanie(ilosc_bomb,kwadracik);
    podlicza_obok(kwadracik,AllX);


	while(okno.isOpen())
	{
	    for(int i=0;i<kwadracik.size();i++)
        {
            if(kwadracik[i].czy_bomba==1)
                if(kwadracik[i].odkryte==0)
                    continue;
                else
                    break;

            if(kwadracik[i].odkryte==0)
                break;

            if(i==kwadracik.size()-1)
            {
                MessageBox(0,"Odnalazles wszystkie miny!","Brawo!",0);
                okno.close();
            }
        }

        if (przegrana)
        {
            MessageBox(0,"Nacisnales na mine!","Porazka!",0);
            okno.close();
        }
		sf::Event zdarzenie;
		while(okno.pollEvent(zdarzenie))
        {
            if(zdarzenie.type==sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                okno.close();
            }
            if(zdarzenie.type==sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button==sf::Mouse::Left)
            {
                for(int i=0;i<kwadracik.size();i++)
                    if(sf::Mouse::getPosition(okno).x>=kwadracik[i].kwadrat.getPosition().x && sf::Mouse::getPosition(okno).x<=kwadracik[i].kwadrat.getPosition().x+kwadracik[i].kwadrat.getSize().x &&
                       sf::Mouse::getPosition(okno).y>=kwadracik[i].kwadrat.getPosition().y && sf::Mouse::getPosition(okno).y<=kwadracik[i].kwadrat.getPosition().y+kwadracik[i].kwadrat.getSize().y)
                        if(kwadracik[i].odkryte==0 && kwadracik[i].flaga==0)
                        {
                            kwadracik[i].odkryte=1;
                            if(kwadracik[i].czy_bomba==1)
                            {
                                for(int j=0;j<kwadracik.size();j++)
                                    kwadracik[j].odkryte=1;
                                przegrana=1;
                            }
                            else if(kwadracik[i].ile_obok==0)
                            {
                                odslanianiepoLPM(kwadracik, AllX);
                            }
                        }

                        else break;
            }
            if(zdarzenie.type==sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button==sf::Mouse::Right)
            {
                for(int i=0;i<kwadracik.size();i++)
                    if(sf::Mouse::getPosition(okno).x>=kwadracik[i].kwadrat.getPosition().x && sf::Mouse::getPosition(okno).x<=kwadracik[i].kwadrat.getPosition().x+kwadracik[i].kwadrat.getSize().x &&
                       sf::Mouse::getPosition(okno).y>=kwadracik[i].kwadrat.getPosition().y && sf::Mouse::getPosition(okno).y<=kwadracik[i].kwadrat.getPosition().y+kwadracik[i].kwadrat.getSize().y)
                        if(kwadracik[i].odkryte==0)
                        {
                            if(kwadracik[i].flaga==0)
                                kwadracik[i].flaga=1;

                            else if(kwadracik[i].flaga==1)
                                kwadracik[i].flaga=0;
                        }

            }
        }


        for(int i=0;i<kwadracik.size();i++)
        {
            if(kwadracik[i].odkryte==0)
            {
                if(kwadracik[i].flaga==0)
                    kwadracik[i].kwadrat.setTexture(&zakryte);
                else if(kwadracik[i].flaga==1)
                    kwadracik[i].kwadrat.setTexture(&flaga);
            }
            else
            {
                if(kwadracik[i].czy_bomba==1)
                    kwadracik[i].kwadrat.setTexture(&mina);
                else
                {
                    if(kwadracik[i].ile_obok==0)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[0]);
                    else if(kwadracik[i].ile_obok==1)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[1]);
                    else if(kwadracik[i].ile_obok==2)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[2]);
                    else if(kwadracik[i].ile_obok==3)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[3]);
                    else if(kwadracik[i].ile_obok==4)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[4]);
                    else if(kwadracik[i].ile_obok==5)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[5]);
                    else if(kwadracik[i].ile_obok==6)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[6]);
                    else if(kwadracik[i].ile_obok==7)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[7]);
                    else if(kwadracik[i].ile_obok==8)
                        kwadracik[i].kwadrat.setTexture(&liczbowe[8]);

                }
            }
        }


        okno.clear();
        for(unsigned int i=0;i<kwadracik.size();i++)
            okno.draw(kwadracik[i].kwadrat);
        okno.display();
	}
}
