//https://www.youtube.com/watch?v=W1_YKBL8m-E
//1:18 created window with sprite
//4:33 created random class
//5:48 created looking mouse
//7:22 created count

#include <SFML/Graphics.hpp>
#include <time.h>
//#include <iostream>



using namespace sf;

class PaintGame
{
    public:
        Texture t;
        Sprite tables[25];

        PaintGame()
        {
            t.loadFromFile("Paint/Schulte tables.png");

            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    tables[j * 5 + i].setTexture(t);
                    tables[j * 5 + i].setTextureRect(IntRect(100 * i, 100 * j, 100, 100));
                    tables[j * 5 + i].setPosition(500 + 100 * i, 100 * j);
                }
            }
        }
};

PaintGame paintgame;

int k = 0;

class RandTables
{
public:
    int a[25];

    RandTables()
    {
        for(int i = 0; i < 25; i++)
            a[i] = 0;

        for(int i = 0; i < 25; i++)
        {
            int tmp = rand() % 25;
            while(a[tmp] != 0)
                tmp = rand() % 25;

            a[tmp] =  i + 1;
        }
        while (k < 25)
        {
            int x = k;
            int y = 0;

            while (x >= 5)
            {
                x -= 5;
                y++;
            }
            paintgame.tables[a[k]-1].setPosition(100 * x, 100 * y);

            k++;
        }
        k = 0;
    }
};

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(650, 500), "Schulte tables");

    RandTables rt;

    Texture ti;
    ti.loadFromFile("Paint/score.png");
    Sprite score(ti);
    score.setPosition(555,250);
    score.setTextureRect(IntRect(0,  0, 24, 38));
    score.setScale(1.5, 1.5);

    Texture ch;
    ch.loadFromFile("Paint/chet.png");
    Sprite chet(ch);
    chet.setPosition(525, 200);

    while(window.isOpen())
    {
        Vector2f ts[25];
        for(int i  = 0; i < 25;  i++)
            ts[i] = paintgame.tables[i].getPosition();
        
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();

            if(event.type == Event::MouseButtonPressed)
                if(event.key.code == Mouse::Left)
                {
                    Vector2i pos = Mouse::getPosition(window);

                    if(pos.x >= ts[k].x && pos.x <= ts[k].x + 100 &&
                       pos.y >= ts[k].y && pos.y <= ts[k].y + 100)
                       k++;
                }
        }

        if(k >= 10)
            score.setPosition(540, 250);

        if(k < 10)
            score.setTextureRect(IntRect(24 * k, 0  ,24, 38));
        else if(k >= 10 && k < 15)
            score.setTextureRect(IntRect(48 * (k-10), 38  ,48, 38));
        else if(k >= 15 && k < 20)
            score.setTextureRect(IntRect(48 * (k-15), 76  ,48, 38));
        else if(k >= 20 && k < 23)
            score.setTextureRect(IntRect(44 + 48 * (k-20), 115  ,48, 38));
        else if(k >= 23)
            score.setTextureRect(IntRect(44 + 48 * (k-23), 153  ,48, 38));

        //std::cout <<  k << "\n";

        window.clear(Color::White);
        for(int i = 0; i < 25; i++)
        {
            window.draw(paintgame.tables[i]); 
        }
        window.draw(score);
        window.draw(chet);
        window.display();
    }

    return 0;
}