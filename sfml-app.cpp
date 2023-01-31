//https://www.youtube.com/watch?v=W1_YKBL8m-E
#include <SFML/Graphics.hpp>

using namespace sf;

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
        window.display();
    }

    return 0;
}