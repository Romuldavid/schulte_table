//https://www.youtube.com/watch?v=W1_YKBL8m-E
#include <SFML/Graphics.hpp>

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

int main()
{
    RenderWindow window(VideoMode(1000, 500), "Schulte tables");

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
            window.draw(paintgame.tables[i]); //1:18
        }
        window.display();
    }

    return 0;
}