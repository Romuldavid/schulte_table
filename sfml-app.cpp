//https://www.youtube.com/watch?v=W1_YKBL8m-E
#include <SFML/Graphics.hpp>
#include <time.h>

//4:33

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
    }
};

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(1000, 500), "Schulte tables");

    RandTables rt;

    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        for(int i = 0; i < 25; i++)
        {
            window.draw(paintgame.tables[i]); 
        }
        window.display();
    }

    return 0;
}