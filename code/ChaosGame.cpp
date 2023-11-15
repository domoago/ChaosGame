//Created by Richard Chao and Dominic Agoncillo
//Created for the CISP 400 Chaos Game Project
//----------------------------------------------//
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

    sf::Font font;

    //setting up the background
    Texture textureBackground;
    Sprite spriteBackground;
    spriteBackground.setPosition(0, 0);

    if (!font.loadFromFile("./fonts/halloweennightmare/Halloween Nightmare.ttf"))
    {
        std::cout << "Error";
    }

    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Chaos Game:\nClick any three points on the screen.\n");

    // set the character size
    text.setCharacterSize(72); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // inside the main loop, between window.clear() and window.display()

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    std::cout << "Click any three points on the screen.\n";
	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    if (vertices.size() >= 2)
                    {
                        text.setString("Chaos Game:\nClick any three points on the screen.\nClick again to start.\n");
                    }
                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        std::cout << "Push back " << vertices.size() << '\n';
                    }
                    else if(points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        
                        //loading the background after the 4th click
                        textureBackground.loadFromFile("graphics/big_fire.png");
                        spriteBackground.setTexture(textureBackground);

                        //std::cout << "fourth point pushed";
                    }
                    //std::cout << "Points Size: " << points.size() << '\n';
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.

            int randomVertex = rand() % 3;
            points.push_back({(vertices[randomVertex].x + points.back().x) / 2, (vertices[randomVertex].y + points.back().y) / 2});
        }

        /*
		****************************************
		Draw
		****************************************
		*/

        if(points.size() < 1) //black background
            window.clear();
        else                  //then grey background after the fourth click
        {
            sf::Color color(50, 50, 50);
            window.clear(color); 
        } 
        
        window.draw(spriteBackground);

        window.draw(text);

        for(int i = 0; i < vertices.size(); i++)
        {
            CircleShape circ(5, 30);
            circ.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            circ.setFillColor(Color::Blue);
            window.draw(circ);
        }
        
        for (int i = 0; i < points.size(); i++)
        {
            CircleShape circ(5, 30);
            circ.setPosition(Vector2f(points[i].x, points[i].y));
            circ.setFillColor(Color::Red);
            window.draw(circ);
        }
        window.display();
    }
}
