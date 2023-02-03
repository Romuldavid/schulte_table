//https://www.youtube.com/watch?v=W1_YKBL8m-E
//1:18 created window with sprite
//4:33 created random class
//5:48 created looking mouse
//7:22 created count
//8:52 true-blue, error-red
//10:35 add watch
//11:39 add sound

#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
//#include <iostream>



using namespace sf;

class setSound
{
    public:
        SoundBuffer e, s,  w, t;
        Sound error, score, win, time;
        bool stopwin;

        setSound()
        {
            e.loadFromFile("Sound/error.ogg");
            s.loadFromFile("Sound/score.ogg");
            w.loadFromFile("Sound/win.ogg");
            t.loadFromFile("Sound/time.ogg");

            error.setBuffer(e);
            score.setBuffer(s);
            win.setBuffer(w);
            time.setBuffer(t);

            time.setLoop(true);

            stopwin = false;
        }
};

setSound sound;

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

class Stopwatch
{
    public:
        Sprite min[2], sec[2], toc;
        int m[2], s[2], ms;

    Stopwatch(Texture& image)
    {
        for(int i = 0; i < 2; i++)
        {
            min[i].setTexture(image);
            sec[i].setTexture(image);

            min[i].setPosition(510 + 30 * i,  25);
            sec[i].setPosition(580 + 30 * i,  25);

            min[i].setTextureRect(IntRect(0, 0, 24, 38));
            sec[i].setTextureRect(IntRect(0, 0, 24, 38));

            m[i] = 0;
            s[i] = 0;

        }
        toc.setTexture(image);
        toc.setPosition(560, 25);
        toc.setTextureRect(IntRect(240, 0, 24, 38));
    }

    void update()
    {
        ms++;

        if(ms >= 1900)
        {
            s[1]++;
            ms = 0;
        }
        if(s[1]  == 10)
        {
            s[0]++;
            s[1] = 0;
        }
        if(s[0]  == 6)
        {
            m[1]++;
            s[0] = 0;
        }
        if(m[1]  == 10)
        {
            m[0]++;
            m[1] = 0;
        }
        for (int i = 0; i < 2; i++) {
			sec[i].setTextureRect(IntRect(24 * s[i], 0, 24, 38));
			min[i].setTextureRect(IntRect(24 * m[i], 0, 24, 38));
		}
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

    int col = 0;
    bool blu = true, stc = false;
    int cx;

    Texture tim;
    tim.loadFromFile("Paint/time.png");
    Stopwatch watch(tim);

    sound.time.play();

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

                    if(col == 0 && k != 25)

                        if(pos.x >= ts[k].x && pos.x <= ts[k].x + 100 &&
                        pos.y >= ts[k].y && pos.y <= ts[k].y + 100){
                        k++;

                        col = 500;
                        blu = true;

                        sound.score.play();
                        }                
                        else
                            for(int i = 0; i < 5; i++)
                                for(int j = 0; j < 5; j++)
                                    if(pos.x >=  ts[j * 5 + i].x && pos.x <= ts[j * 5 + i].x + 100 &&
                                    pos.y >=  ts[j * 5 + i].y && pos.y <= ts[j * 5 + i].y + 100)
                                    {
                                        col = 500;
                                        blu = false;

                                        cx = j * 5 + i;

                                        sound.error.play();
                                    }
                }
        }

        if(col > 0)
        {
            col--;
            stc = true;

            if(blu)
                paintgame.tables[k - 1].setColor(Color::Blue);
            else
                paintgame.tables[cx].setColor(Color::Red);
        }
        else if (col == 0 && stc)
        {
            if(blu)
                paintgame.tables[k - 1].setColor(Color::White);
            else
                paintgame.tables[cx].setColor(Color::White);
        }

        if(k == 25 && col == 0)
            for(int i = 0; i < 25; i++)
                paintgame.tables[i].setColor(Color::Green);

        if(k  == 25 && !sound.stopwin)
        {
            sound.win.play();
            sound.time.stop();

            sound.stopwin = true;
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

        if( k != 25)
            watch.update();
        
        window.clear(Color::White);
        for(int i = 0; i < 25; i++)
        {
            window.draw(paintgame.tables[i]); 
        }
        window.draw(score);
        window.draw(chet);

        for(int i = 0; i < 2;  i++)
        {
            window.draw(watch.min[i]);
            window.draw(watch.sec[i]);
        }
        window.draw(watch.toc);
        window.display();
    }

    return 0;
}